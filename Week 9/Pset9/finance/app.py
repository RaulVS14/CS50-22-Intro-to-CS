import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash, safe_str_cmp

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
app.config["SESSION_FILE_DIR"] = "app_session"
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
    user = session["user_id"]
    stocks = db.execute("SELECT symbol, name, SUM(shares) as shares FROM purchases WHERE user_id = ? GROUP BY symbol",
                        user)
    user_data = db.execute("SELECT id, cash FROM users WHERE id = ?", user)
    total = 0
    cash = 0
    if len(user_data) == 1 and stocks:
        cash = user_data[0]['cash']
        total += cash
        for stock in stocks:
            stock_data = lookup(stock['symbol'])
            if stock_data:
                stock['price'] = stock_data['price']
                stock['total'] = stock['shares'] * stock_data['price']
                total += stock['total']
    return render_template("index.html", total=total, stocks=stocks, cash=cash)


def is_valid_shares(shares):
    if not shares:
        return False
    try:
        int_shares = int(shares)
        if 1 > int(int_shares):
            return False
    except ValueError as _:
        return False
    return True


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # Ensure symbol was submitted
        if not symbol:
            return apology("must provide symbol", 400)

        # Ensure symbol was correct
        stock = lookup(symbol)
        if not stock:
            return apology("must provide correct symbol")

        # Ensure shares was correctly submitted
        if not is_valid_shares(shares):
            return apology("must provide positive integer", 400)

        user_id = session.get('user_id')
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        if stock and len(rows) == 1:
            user_cash = rows[0]['cash']
            total_cost = int(shares) * stock['price']
            # user_id, symbol, name, price, shares, timestamp, total
            if user_cash < total_cost:
                return apology(f"not enough cash to buy {shares} for {stock['price']}")

            db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash - total_cost, user_id)
            db.execute(
                "INSERT INTO purchases "
                "(user_id, symbol, name, price, shares, total, timestamp) "
                "VALUES (?, ?, ?, ?, ?, ?, datetime('now'))",
                user_id, stock['symbol'], stock['name'], stock['price'], shares, total_cost)
            flash(
                f"Purchase successful! Bought {shares} shares of {stock['symbol']} for {usd(stock['price'])}. Total cost was {usd(total_cost)}")
            return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
                rows[0]["hash"], request.form.get("password")):
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
        # Ensure symbol was provided
        if not symbol:
            return apology("must provide symbol", 400)
        data = lookup(symbol)
        if not data:
            return apology("Symbol doesn't exist", 400)
        return render_template("quote.html", symbol=symbol, data=data)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)
        else:
            rows = db.execute("SELECT * FROM users where username = ?", username)
            if len(rows) == 1:
                return apology("username already exists", 403)
        # Ensure password was submitted
        if not password:
            return apology("must provide password", 400)
        # Ensure confirmation was submitted
        if not confirmation:
            return apology("must confirm password", 400) \
                # Ensure passwords match
        if password and confirmation and not safe_str_cmp(password, confirmation):
            return apology("passwords must match", 400)

        db.execute("INSERT INTO users (username, hash, cash) VALUES (?, ?, 0)", username,
                   generate_password_hash(password))
        # Redirect user to home page
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
