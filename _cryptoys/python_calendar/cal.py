weeks_per_line = 4

cells_per_line = 7 * weeks_per_line
string_cal = ""

string_cal += "<html>"
string_cal += "<head>"
string_cal += "<style type='text/css'>"
string_cal += "table{border-collapse:collapse;}"
string_cal += "body{font-family:monospace;}"
string_cal += "td {border:1px solid black;}"
string_cal += ""
string_cal += "</style>"
string_cal += "</head>"
string_cal += "<body>"

string_cal += ""
string_cal += ""
string_cal += "<table>"
single_week = "<td>MO</td><td>TU</td><td>WE</td><td>TH</td><td>FR</td><td>SA</td><td>SU</td>"


f = open("calendar.html", "w")

for a in range(4 * 12):
    string_cal += "<tr>" + single_week + single_week + single_week + single_week + "</tr>\n"
string_cal += "</table>"
string_cal + "</body></html>"

f.write(string_cal)
