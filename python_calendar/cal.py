weeks_per_line = 4

cells_per_line = 7 * weeks_per_line

string_cal = ""
string_cal += "<table>\n"
single_week = "<td>MO</td><td>TU</td><td>WE</td><td>TH</td><td>FR</td><td>SA</td><td>SU</td>"

string_cal += "<tr>" + single_week + single_week + single_week + single_week + "</tr>\n"
string_cal += "</table>\n"

f = open("calendar.html", "w")

for a in range(4 * 12):
    f.write(string_cal)

