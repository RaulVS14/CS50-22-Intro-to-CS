from flask import Flask, render_template, request, redirect, session
from flask_mail import Mail, Message
from flask_session import Session
from sql import SQL
import os
import re

app = Flask(__name__)
db = SQL("sqlite:///froshims.db")

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem" # can be db, memory, RAM, etc
Session(app)

BASE_TITLE = "APP"

# Requires "Less secure app access" to be on
# https://support.google.com/accounts/answer/6010255
# app.config["MAIL_DEFAULT_SENDER"] = os.environ["MAIL_DEFAULT_SENDER"]
# app.config["MAIL_PASSWORD"] = os.environ["MAIL_PASSWORD"]
# app.config["MAIL_USERNAME"] = os.environ["MAIL_USERNAME"]
# app.config["MAIL_PORT"] = 587
# app.config["MAIL_SERVER"] = "smtp.gmail.com"
# app.config["MAIL_USE_TLS"] = True
# mail = Mail(app)

SPORTS = [
    "Basketball",
    "Football",
    "Discgolf"
]

def invalid_session(session):
    print(session.get('name'))
    return not session.get('name')


@app.route("/")
def index():
    if invalid_session(session):
        return redirect("/login")
    title = f"HOME | {BASE_TITLE}"
    return render_template("index.html", title=title, sports=SPORTS)

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        session["name"] = request.form.get("name")
        return redirect("/")
    return render_template("/login.html")


@app.route("/logout", methods=["POST"])
def logout():
    if request.method == "POST":
        session["name"] = None
        return redirect("/")
    return redirect("/")

@app.route("/register", methods=["POST"])
def register():
    if invalid_session(session):
        return redirect("/login")
    title = f"Registration | {BASE_TITLE}"
    name = request.form.get("name")
    email = request.form.get("email")
    sport = request.form.get("sport")
    if not name:
        return render_template("failure.html", message="Missing name")
    if not email:
        return render_template("failure.html", message="Missing email")
    if not sport:
        return render_template("failure.html", message="Missing sport")
    if sport not in SPORTS:
        return render_template("failure.html", message="Invalid sport")
    # message = Message("You are registered!", recipients=[email])
    # mail.send(message)

    db.execute("INSERT INTO registrants (name, email, sport) VALUES (?, ?, ?)", name, email,sport)

    return render_template("success.html", title=title, name=name)


@app.route("/registrants")
def registrants():
    if invalid_session(session):
        return redirect("/login")
    title = f"Registrants | {BASE_TITLE}"
    registrants = db.execute("SELECT id, name, sport FROM registrants")
    return render_template("registrants.html", title=title, registrants=registrants)


@app.route("/deregister", methods=["POST"])
def deregister():
    if invalid_session(session):
        return redirect("/login")
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")
