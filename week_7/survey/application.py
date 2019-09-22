import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    form_values = {}
    missing_values = []

    form_values['first_name'] = request.form["firstname"]
    form_values['last_name'] = request.form["lastname"]
    form_values['favorite_color'] = request.form.get("color")
    form_values['favorite_programming'] = request.form.get("programming")
    form_values['comment'] = request.form["comment"]

    for key, value in form_values.items():
        if value is None or len(value) == 0:
            missing_values.append(key)

    if len(missing_values) > 0:
        missing_values = [x.replace('_', " ") for x in missing_values]
        error_message = "Please provided the following missing values: {}".format(', '.join(missing_values))
        return render_template("error.html", message=error_message)

    csv_fieldnames = ['firstname', 'lastname', 'color', 'programming', 'comment']

    with open('survey.csv', 'a') as file:
        writer = csv.DictWriter(file, fieldnames=csv_fieldnames)
        writer.writerow({'firstname': form_values['first_name'],
                         'lastname': form_values['last_name'],
                         'color': form_values['favorite_color'],
                         'programming': form_values['favorite_programming'],
                         'comment': form_values['comment']})
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    rows = {}
    with open("survey.csv", "r") as file:
        reader = csv.reader(file)
        rows = list(reader)
        print(rows)
        return render_template("sheet.html", rows=rows)
    return render_template("error.html", message="Error extracting CSV data")
