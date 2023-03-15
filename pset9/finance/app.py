import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
import re

from helpers import apology, login_required, lookup, usd, password_check, validation_character

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    ID = session["user_id"]
    rows = db.execute("SELECT * FROM portfolio WHERE user_id = ?", ID)

    quote = []
    for row in rows:
        quote.append(lookup(row["symbol"]))

    cash = db.execute("SELECT cash FROM users WHERE id = ?", ID)
    cash = cash[0]["cash"]

    total = cash
    for row in quote:
        for shares in rows:
            if ( row["symbol"] == shares["symbol"]):
                total += row["price"] * shares["shares"]


    return render_template("index.html", rows=rows, quote=quote, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Check for valid input
        symbol = request.form.get("symbol").upper()
        if not symbol:
            return apology("Please provide a stock symbol", 400)

        shares = request.form.get("shares")
        if not shares or not shares.isnumeric() or int(shares) <= 0:
            return apology("Please provide a number of shares", 400)

        # Get quote
        quote = lookup(symbol)
        if quote == None:
            return apology("Please provide a valid stock symbol", 400)

        # Check if the user have enough cash
        ID = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", ID)

        shares = int(shares)
        price = quote["price"]
        cash = cash[0]["cash"] - shares * price
        if cash < 0:
            return apology("You don't have enough cash", 403)


        # Buy shares of stocks
        db.execute("pragma foreign_keys = on")

        db.execute("UPDATE users SET cash=?  WHERE id =? ", cash, ID)

        rows = db.execute("SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", ID, symbol)
        if len(rows) == 1:
            Shares = int(rows[0]["shares"]) + shares
            db.execute("UPDATE portfolio SET shares=? WHERE user_id = ? AND symbol = ?", Shares, ID, symbol)
        else:
            db.execute("INSERT INTO portfolio(user_id, symbol, shares) VALUES(?, ?, ?)", ID, symbol, shares)

        # history
        name = quote["name"]
        time = db.execute("SELECT time('now')")[0]["time('now')"]
        date = db.execute("SELECT date('now')")[0]["date('now')"]
        db.execute("INSERT INTO history(type, name, symbol, shares, price, date, time, user_id) VALUES(?, ?, ?, ?, ?, ?, ?, ?)",
                    "Bought", name, symbol, shares, price, date, time, ID)

        return redirect("/")

    return render_template("buy.html")




@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    ID = session["user_id"]
    rows = db.execute("SELECT type,name, symbol,shares,price,date,time FROM history WHERE user_id = ?", ID)

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please provide a stock symbol", 400)
        print(type(symbol))
        quote = lookup(symbol)
        print(quote)
        if quote == None:
            return apology("Please provide a valid stock symbol", 400)

        return render_template("quoted.html", quote=quote)


    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)

        if  len(username) < 4:
            return apology("Your username should be minimum 4 characters", 403)

        elif not password:
            return apology("must provide password", 400)

        elif not confirmation:
            return apology("must re-enter password", 400)

        elif password != confirmation:
            return apology("your password do not match. please try again", 400)

        elif not password_check(password):
            return apology("your password should be: Minimum 8 characters, At least one: Lower Case character, Upper Case character, Number and Specia character", 403)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure the username is unique
        if len(rows) == 1:
            return apology("username already taken", 400)

        # register users
        password_hash = generate_password_hash(password)
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", username, password_hash)

        # Remember which user has logged in
        User_id = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = User_id[0]["id"]

        db.execute("INSERT INTO account(user_id) VALUES(?)", User_id[0]["id"])

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    ID = session["user_id"]
    rows = db.execute("SELECT * FROM portfolio WHERE user_id = ?", ID)

    symbols = []
    for row in rows:
        symbols.append(row["symbol"])

    if request.method == "POST":
        stock = request.form.get("symbol")
        shares = request.form.get("shares")

        if not stock:
            return apology("Please choose a stock", 400)

        if stock not in symbols:
            return apology("You don't have this stock", 400)

        if not shares or not shares.isnumeric() or int(shares) <= 0:
            return apology("Please provide a number of shares", 400)

        db.execute("pragma foreign_keys = on")

        Shares = db.execute("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?", ID, stock)
        Shares = Shares[0]["shares"]

        shares = int(shares)
        if shares > Shares:
            return apology("You don't have enough shares", 400)


        # Sell the stock
        Shares = Shares - shares
        db.execute("UPDATE portfolio SET shares=?  WHERE user_id =? AND symbol = ?", Shares, ID, stock)

        cash = db.execute("SELECT cash FROM users WHERE id =? ", ID)
        cash = cash[0]["cash"]

        quote = lookup(stock)
        price = quote["price"]
        cash += price * shares

        db.execute("UPDATE users SET cash=?  WHERE id =? ", cash, ID)

        if Shares == 0:
            db.execute("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", ID, stock)

        # history
        name = quote["name"]
        time = db.execute("SELECT time('now')")[0]["time('now')"]
        date = db.execute("SELECT date('now')")[0]["date('now')"]
        db.execute("INSERT INTO history(type, name, symbol, shares, price, date, time, user_id) VALUES(?, ?, ?, ?, ?, ?, ?, ?)",
                    "Sold", name, stock, - shares, price, date, time, ID)

        return redirect("/")

    return render_template("sell.html", symbols=symbols)


@app.route("/account")
@login_required
def account():
    ID = session["user_id"]
    rows = db.execute("SELECT username,cash FROM users WHERE id = ?", ID)
    username = rows[0]["username"]
    cash = rows[0]["cash"]

    rows_2 = db.execute("SELECT * FROM account WHERE user_id = ?", ID)


    return render_template("account.html", username=username, cash=cash, rows=rows_2)


@app.route("/edit", methods=["GET", "POST"])
@login_required
def edit():
    ID = session["user_id"]
    """ Edit user information """

    if request.method == "POST":

        rows = db.execute("SELECT * FROM account WHERE user_id = ?", ID)
        if len(rows) != 1:
            db.execute("INSERT INTO account(user_id) VALUES(?)", ID)

        if request.form.get("first_name"):
            first_name = request.form.get("first_name")
            db.execute("UPDATE account SET first_name=?  WHERE user_id =?", first_name, ID)

        if request.form.get("last_name"):
            last_name = request.form.get("last_name")
            db.execute("UPDATE account SET last_name=?  WHERE user_id =?", last_name, ID)

        if request.form.get("age"):
            age = request.form.get("age")
            if not age.isnumeric():
                return apology("Age must be a number", 403)
            db.execute("UPDATE account SET age=?  WHERE user_id =?", age, ID)

        if request.form.get("phone_number"):
            phone_number = request.form.get("phone_number")
            db.execute("UPDATE account SET phone_number=?  WHERE user_id =?", phone_number, ID)

        if request.form.get("email"):
            email = request.form.get("email")

            pat = "^[a-zA-Z0-9-_]+@[a-zA-Z0-9]+\.[a-z]{1,3}$"
            if not re.match(pat,email):
                return apology("Email not valid", 403)

            db.execute("UPDATE account SET email=?  WHERE user_id =?", email, ID)

        return redirect("/account")

    return render_template("edit_account.html")



@app.route("/change_password", methods=["POST"])
@login_required
def change_password():
    ID = session["user_id"]
    """ change password """

    if request.method == "POST":
        if request.form.get("new_password") and not request.form.get("current_password"):
            return apology("must provided the current password", 403)

        if request.form.get("new_password") and request.form.get("current_password"):

            current_password = request.form.get("current_password")
            new_password = request.form.get("new_password")

            rows = db.execute("SELECT * FROM users WHERE id = ?", ID)

            if not check_password_hash(rows[0]["hash"], current_password):
                return apology("Current password not correct", 403)


            elif not password_check(new_password):
                return apology("your password should be: Minimum 8 characters, At least one: Lower Case character, Upper Case character, Number and Specia character", 403)

            password_hash = generate_password_hash(new_password)
            db.execute("UPDATE users SET hash=?  WHERE id =? ", password_hash, ID)

            return redirect("/account")


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    if request.method == "POST":
        cash = request.form.get("cash")
        if not cash or not cash.isnumeric() or int(cash) <= 0:
            return apology("Please enter how much you want to add to your balance", 403)

        currency = request.form.get("currency")
        if currency != '$':
            return apology("Please choose a valid currency", 403)


        # credit/debit validation
        nameoncard = request.form.get("nameoncard")
        cardnumber = request.form.get("cardnumber")
        cvv = request.form.get("cvv")
        experationdate = request.form.get("experationdate")

        if not nameoncard or not cardnumber or not cvv or not experationdate:
            return apology("Please provide credit/debit card details", 403)

        if not cvv.isnumeric() or int(cvv) == 3 or int(cvv) == 4:
            return apology("CVV number invalid", 403)


        format_mmyyyy = "%m/%Y"
        try:
            date = datetime.strptime(experationdate, format_mmyyyy)
            date = 0;
        except ValueError:
            date = 1;
        if not date == 0:
            return apology("Your card experation date not valid", 403)

        # checking card number - ex: 5512118197853260
        if not cardnumber.isnumeric():
            return apology("Your card number not valid", 403)

        l = len(cardnumber)
        validation = validation_character(cardnumber, l)

        if validation != 0:
            return apology("Your card number not valid", 403)

        ID = session["user_id"]
        rows = db.execute("SELECT cash FROM users WHERE id = ?", ID)

        cash = int(cash) + rows[0]["cash"]
        db.execute("UPDATE users SET cash=? WHERE id = ?", cash, ID)
        return redirect("/")

    return render_template("deposit.html")

@app.route("/delete", methods=["GET", "POST"])
@login_required
def delete():
    if request.method == "POST":
        ID = session["user_id"]
        if request.form.get("delete"):
            db.execute("DELETE FROM portfolio WHERE user_id = ?", ID)
            db.execute("DELETE FROM history WHERE user_id = ?", ID)
            db.execute("DELETE FROM account WHERE user_id = ?", ID)
            db.execute("DELETE FROM users WHERE id = ?", ID)
            session.clear()
            return render_template("delete.html")

