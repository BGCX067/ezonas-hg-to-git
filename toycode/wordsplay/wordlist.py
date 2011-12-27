# input must be space separated words, do in notepad++
def clean_word_list(filename_r, filename_w):
	file_r = open(filename_r, "r")
	file_w = open(filename_w, "w")
	
	string = file_r.read()
	words = string.split(' ')
	
	cleaned = '\n'.join(sorted(set(words)))
	
	file_w.write(cleaned)

	file_r.close()
	file_w.close()
	print cleaned
	
clean_word_list("words-1line.txt", "words.txt")