from flask import Flask, render_template, request

app = Flask(__name__)

BASE_TITLE = "APP"
@app.route("/")
def index():
    title = f"HOME | {BASE_TITLE}"
    return render_template("index.html", title=title)


@app.route("/greet", methods=['POST'])
def greet():
    name = request.form.get('name', 'World')
    name = 'Worlde' if name == '' else name
    title = f"Greet {BASE_TITLE}"
    return render_template("greet.html", name=name, title=title)