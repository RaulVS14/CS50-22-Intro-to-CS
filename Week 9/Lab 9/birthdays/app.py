import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


def is_valid_date(day, month):

    if not day:
        return False, "Name is required"

    if not month:
        return False, "Month is required"
    months_30_days = [4, 6, 9, 11]
    month_february = 2
    if not 1 <= month <= 12:
        return False, "Incorrect month"

    if not 1 <= day <= 31:
        return False, "Incorrect day"

    message = None
    condition_30_days = (month in months_30_days) and (1 <= day <= 30)
    condition_february_days = (month == month_february) and (1 <= day <= 29)
    condition_31_days = ((month not in months_30_days) and (
        month != month_february) and (1 <= day <= 31))
    if not (condition_30_days or condition_february_days or condition_31_days):
        return False, "Incorrect date!"
    return True, message


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        id = request.form.get("id")
        if not name:
            return render_template("error.html", message="Name is required")
        try:
            month = int(request.form.get("month"))
            day = int(request.form.get("day"))
        except ValueError as e:
            return render_template("error.html", message="Incorrect date values")
        valid_date, message = is_valid_date(day, month)
        if not valid_date:
            return render_template("error.html", message=message)

        # Add the user's entry into the database
        if not id:
            db.execute(
                "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        else:
            db.execute(
                "UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", name, month, day, id)
        return redirect("/")
    else:
        # Display the entries in the database on index.html
        birthdays = db.execute("SELECT id, name, month,day FROM birthdays")
        return render_template("index.html", birthdays=birthdays)


@app.route("/remove", methods=["POST"])
def remove():
    if request.method == "POST":
        id = request.form.get('id')
        if id:
            db.execute("DELETE FROM birthdays WHERE id=?", id)
    return redirect("/")


@app.route("/edit", methods=["POST"])
def edit():
    if request.method == "POST":
        id = request.form.get('id')
        if id:
            birthdays = db.execute(
                "SELECT id, name, month, day FROM birthdays WHERE id = ?", id)
            if birthdays:
                return render_template("edit.html", birthday=birthdays[0], id=id)
            return render_template("error.html", message="No birthdays found!")
        return render_template("error.html", message="Incorrect query")
    return redirect("/")
