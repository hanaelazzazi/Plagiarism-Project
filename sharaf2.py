from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

def compare_sentences(sentence1, sentence2):
    # Create a TF-IDF vectorizer
    vectorizer = TfidfVectorizer()

    # Vectorize the sentences
    sentence_vectors = vectorizer.fit_transform([sentence1, sentence2])

    # Calculate the cosine similarity between the vectors
    similarity = cosine_similarity(sentence_vectors)[0][1]

    return (similarity*100)
import sys

# main
#sentence1= sys.argv[1]
#sentence2= sys.argv[2]
#print('Params=', param_1, param_2)



filename = "/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Python/dump.txt"


with open(filename, 'r') as f:
    lines = f.readlines()
    if len(lines) < 2:
        print("Error: file has less than two lines")
    else:
        first_line = lines[0].strip()
        second_line = lines[1].strip()







with open(first_line, 'r') as file:
    content1 = file.read()
        
        
with open(second_line, 'r') as file1:
    content = file1.read()
    
    


similarity = compare_sentences(content, content1)




with open(filename, "w") as f2:
    # Write the new data to the file
    f2.write(str(similarity))


    f2.close()