# -*- coding: utf8 -*-
import sys
l = [
"NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL",
"BS", "HT", "LF", "VT", "FF", "CR","SO", "SI", 
      
"DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB",
"CAN","EM", "SUB","ESC","FS", "GS", "RS", "US"
]
names = [
"Null character",
"Start of Header",
"Start of Text",
"End of Text",
"End of Transmission",
"Enquiry",
"Acknowledgment",
"Bell",
"Backspace",
"Horizontal Tab",
"Line feed",
"Vertical Tab",
"Form feed",
"Carriage return",
"Shift Out",
"Shift In",
"Data Link Escape",
"Device Control 1",
"Device Control 2",
"Device Control 3",
"Device Control 4",
"Negative Acknowledgement",
"Synchronous idle",
"End of Transmission Block",
"Cancel",
"End of Medium",
"Substitute",
"Escape",
"File Separator",
"Group Separator",
"Record Separator",
"Unit Separator",
"Delete"
]
names_short = [
"NULL",
"START HEADER",
"START TEXT",
"END OF TEXT",
"END TRANSM.",
"ENQUIRY",
"ACKNOWLEDGMENT",
"BELL",
"BACKSPACE",
"HOR. TAB",
"LINE FEED",
"VER. TAB",
"FORM FEED",
"CARR. RETURN",
"SHIFT OUT",
"SHIFT IN",
"DATA LINK ESC.",
"DEV CTRL1",
"DEV CTRL2",
"DEV CTRL3",
"DEV CTRL4",
"NEG. ACK",
"SYNCHRONOUS IDLE",
"END TRANSM. BLOCK",
"CANCEL",
"END OF MEDIUM",
"SUBSTITUTE",
"ESCAPE",
"FILE SEP.",
"GROUP SEP.",
"RECORD SEP.",
"UNIT SEP.",
"DELETE"
]
a = []
# for c in range(64, 96):
# 	a.append(chr(c))
# d = dict(zip(a, l))

# for c in range(64, 96):
# 	print chr(c), d[chr(c)],

# f = u'␀'
un = [
u'␀', u'␁', u'␂', u'␃', u'␄', u'␅', u'␆', u'␇', u'␈', u'␉', u'␊', u'␋', u'␌', u'␍', u'␎', u'␏', u'␐', u'␑', u'␒', u'␓', u'␔', u'␕', u'␖', u'␗', u'␘', u'␙', u'␚',
 # u'␛',
 u'␛',
u'␜', u'␝', u'␞', u'␟', u'␡'
]


print "<html>"
print "<head>"

print "<style type='text/css'>"
print "body {font-family: monospace;}"
print 'tr.specials {font-family: "Apple Symbols"; font-size:130%;}'
print "td {padding: 5px;}"
print "</style>"

print "<meta charset='utf-8'>"
# print "</head><body><pre><table>"
print "</head><body><table>"

print '<tr>'
for n in range(-1, 16):
	# print "<td>", hex(n)[-1].upper(), '</td>',
	print "<td>", n, '</td>',
print '</tr>'

print '<tr>'
for n in range(32):
	if not n % 16:
		print '<td>', str(n-1),'</td></tr><tr class="specials"><td>', str(n), '</td>'
		# print '</tr><tr class="specials"><td>', str(n / 16), '</td>'
	print '<td>', un[n].encode('utf-8'), '</td>'
print '</tr>'


print '<tr>'
for n in range (32, 128):
	if not n % 16:
		# print '</tr><tr><td>', str(n / 16), '</td>'
		print '<td>', str(n-1),'</td></tr><tr><td>', str(n), '</td>'
	print '<td>', chr(n), '</td>'
print '</tr>'

print "</table></body></html>"
# print "</table></pre></body></html>"
