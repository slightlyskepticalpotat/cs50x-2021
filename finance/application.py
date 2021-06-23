import datetime
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    total = 0
    stocks = db.execute("SELECT * FROM buys WHERE user_id = ?", session["user_id"])
    for stock in stocks:
        stock["price"] = lookup(stock["symbol"])["price"]
        total += stock["price"] * stock["shares"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    return render_template("index.html", cash=cash[0]["cash"], total=total, data=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        quote = lookup(request.form.get("symbol"))
        if quote:
            if not request.form.get("shares"):
                return apology("must provide shares", 400)
            if not request.form.get("shares").isnumeric() or not int(request.form.get("shares")):
                return apology("shares must be positive integers", 400)
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            if quote["price"] * int(request.form.get("shares")) > cash[0]["cash"]:
                return apology("cannot afford", 400)
            db.execute("UPDATE users SET cash = ?", cash[0]["cash"] - quote["price"] * int(request.form.get("shares")))
            db.execute("INSERT INTO buys (user_id, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?)", session["user_id"],
                       request.form.get("symbol"), request.form.get("shares"), quote["price"], str(datetime.datetime.now()))
            # Redirect user to home page
            return redirect("/")
        else:
            return apology("invalid symbol", 400)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return redirect("/")


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
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        quote = lookup(request.form.get("symbol"))
        if quote:
            return render_template("quote.html", price=quote["price"])
        else:
            return apology("invalid symbol", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        data = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if data:
            return apology("username already exists", 400)
        if not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 400)
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)
        if len(request.form.get("password")) < 8:
            return apology("passwords must be at least 8 chars", 400)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))
        return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        if not request.form.get("shares").isnumeric() or not int(request.form.get("shares")):
            return apology("shares must be positive integers", 400)
        owned = db.execute("SELECT SUM(shares) FROM buys WHERE user_id = ?", session["user_id"])[0]["SUM(shares)"]
        if owned < int(request.form.get("shares")):
            return apology("you do not own that many shares", 400)
        return redirect("/")
    else:
        select_options = db.execute("SELECT DISTINCT symbol FROM buys WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", select_options=select_options)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
