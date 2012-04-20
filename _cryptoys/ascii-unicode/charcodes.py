print "<html>"
print "<head>"

print "<style type='text/css'>"
print "body {font-family: 'Arial';}"

# print "body {font-family: 'Helvetica';}"
# print "body {font-family: monospace;}"
# print 'tr.specials {font-family: "Apple Symbols"; font-size:130%;}'
print "td {padding: 5px;font-size:150%;}"
print "</style>"

print "<meta charset='utf-8'>"
# print "<meta charset='ISO-8859-1'>"
# print "</head><body><pre><table>"
print "</head><body>"


def uni_range(a, b, s = 0):
	if s == 0:
		s = str(a) + "-" + str(b)
	print "<h1>"+s+"</h1>"
	print "<p>", str(a)+'-'+str(b), hex(a)+'-'+hex(b), "</p>"
	print "<table><tr>"
	
	for a in range(a, b):
		if not a % 16:
			print "</tr><tr>"
			print "<th>" + hex(a) +"</th>"
		print "<td>&#"+str(a)+";</td>"
		# print "<td>&#"+unichr(a)+";</td>"
	print "</tr></table>"

# uni_range(0,127      , "Basic Latin"                                    )
# uni_range(128,255    , "Latin-1 Supplement"                             )
# uni_range(256,383    , "Latin Extended-A"                               )
# uni_range(384,591    , "Latin Extended-B"                               )
uni_range(592,687    , "IPA Extensions"                                 )
# uni_range(688,767    , "Spacing Modifier Letters"                       )
# uni_range(768,879    , "Combining Diacritical Marks"                    )
uni_range(880,1023   , "Greek"                                          )
uni_range(1024,1279  , "Cyrillic"                                       )
uni_range(1328,1423  , "Armenian"                                       )
uni_range(1424,1535  , "Hebrew"                                         )
uni_range(1536,1791  , "Arabic"                                         )
# uni_range(1792,1871  , "Syriac  "                                       )
# uni_range(1920,1983  , "Thaana"                                         )
uni_range(2304,2431  , "Devanagari"                                     )
# uni_range(2432,2559  , "Bengali"                                        )
uni_range(2560,2687  , "Gurmukhi"                                       )
uni_range(2688,2815  , "Gujarati"                                       )
# uni_range(2816,2943  , "Oriya"                                          )
uni_range(2944,3071  , "Tamil"                                          )


# uni_range(3072,3199  , "Telugu"                                         )
# uni_range(3200,3327  , "Kannada"                                        )
# uni_range(3328,3455  , "Malayalam"                                      )
# uni_range(3456,3583  , "Sinhala"                                        )
uni_range(3584,3711  , "Thai"                                           )
uni_range(3712,3839  , "Lao"                                            )
uni_range(3840,4095  , "Tibetan"                                        )
# uni_range(4096,4255  , "Myanmar "                                       )
uni_range(4256,4351  , "Georgian"                                       )
uni_range(4352,4607  , "Hangul Jamo"                                    )
# uni_range(4608,4991  , "Ethiopic"                                       )
uni_range(5024,5119  , "Cherokee"                                       )
uni_range(5120,5759  , "Unified Canadian Aboriginal Syllabics"          )
uni_range(5760,5791  , "Ogham"                                          )
uni_range(5792,5887  , "Runic"                                          )
# uni_range(6016,6143  , "Khmer"                                          )
uni_range(6144,6319  , "Mongolian"                                      )
# uni_range(7680,7935  , "Latin Extended Additional"                      )
uni_range(7936,8191  , "Greek Extended"                                 )
# uni_range(8192,8303  , "General Punctuation"                            )
# uni_range(8304,8351  , "Superscripts and Subscripts"                    )
# uni_range(8352,8399  , "Currency Symbols"                               )
# uni_range(8400,8447  , "Combining Marks for Symbols"                    )
# uni_range(8448,8527  , "Letterlike Symbols"                             )
# uni_range(8528,8591  , "Number Forms"                                   )
# uni_range(8592,8703  , "Arrows"                                         )
uni_range(8704,8959  , "Mathematical Operators"                         )
uni_range(8960,9215  , "Miscellaneous Technical"                        )
uni_range(9216,9279  , "Control Pictures"                               )
# uni_range(9280,9311  , "Optical Character Recognition"                  )
# uni_range(9312,9471  , "Enclosed Alphanumerics"                         )
# uni_range(9472,9599  , "Box Drawing"                                    )
# uni_range(9600,9631  , "Block Elements"                                 )
uni_range(9632,9727  , "Geometric Shapes"                               )
uni_range(9728,9983  , "Miscellaneous Symbols"                          )
# uni_range(9984,10175 , "Dingbats"                                       )
# uni_range(10240,10495, "Braille Patterns"                               )
# uni_range(11904,12031, "CJK Radicals Supplement"                        )
uni_range(12032,12255, "Kangxi Radicals"                                )
uni_range(12272,12287, "Ideographic Description Characters"             )
uni_range(12288,12351, "CJK Symbols and Punctuation"                    )
uni_range(12352,12447, "Hiragana"                                       )
uni_range(12448,12543, "Katakana"                                       )
# uni_range(12544,12591, "Bopomofo"                                       )
uni_range(12592,12687, "Hangul Compatibility Jamo"                      )
uni_range(12688,12703, "Kanbun"                                         )
# uni_range(12704,12735, "Bopomofo Extended"                              )
# uni_range(12800,13055, "Enclosed CJK Letters and Months"                )
uni_range(13056,13311, "CJK Compatibility"                              )
# uni_range(13312,19893, "CJK Unified Ideographs Extension A"             )
# uni_range(19968,40959, "CJK Unified Ideographs"                         )
uni_range(40960,42127, "Yi Syllables"                                   )
uni_range(42128,42191, "Yi Radicals"                                    )
# uni_range(44032,55203, "Hangul Syllables"                               )
# uni_range(55296,56191, "High Surrogates"                                )
# uni_range(56192,56319, "High Private Use Surrogates"                    )
# uni_range(56320,57343, "Low Surrogates"                                 )
# uni_range(57344,63743, "Private Use"                                    )
# uni_range(63744,64255, "CJK Compatibility Ideographs"                   )
uni_range(64256,64335, "Alphabetic Presentation Forms"                  )
# uni_range(64336,65023, "Arabic Presentation Forms-A"                    )
# uni_range(65056,65071, "Combining Half Marks"                           )
uni_range(65072,65103, "CJK Compatibility Forms"                        )
# uni_range(65104,65135, "Small Form Variants"                            )
# uni_range(65136,65278, "Arabic Presentation Forms-B"                    )
# uni_range(65279,65279, "Specials"                                       )
# uni_range(65280,65519, "Halfwidth and Fullwidth Forms"                  )
# uni_range(65520,65533, "Specials"                                       )
	
print "</body></html>"
