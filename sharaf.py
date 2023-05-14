import torch
from transformers import DistilBertTokenizer, DistilBertForSequenceClassification

# load the pre-trained DistilBERT model and tokenizer
model = DistilBertForSequenceClassification.from_pretrained('distilbert-base-uncased-finetuned-sst-2-english')
tokenizer = DistilBertTokenizer.from_pretrained('distilbert-base-uncased-finetuned-sst-2-english')

# function to detect AI generated text using DistilBERT
def is_ai_generated(content):
    # read the contents of the file
   # with open(filename, 'r') as file:
      #  content = file.read()
    

    # encode the text with the tokenizer
    inputs = tokenizer(content, return_tensors='pt')

    # run the model prediction
    outputs = model(**inputs)

    # get the predicted label (0 = not AI generated, 1 = AI generated)
    predicted_label = torch.argmax(outputs[0])

    # return True if the predicted label is 1 (AI generated), False otherwise
    return predicted_label.item() == 1
filename = "/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Python/dump.txt" # change the file name to your desired file name


with open(filename, "r") as file:
   
    content = file.read()


    


    x = is_ai_generated(content)
    
    
    file.close()
    
    
print(x)


with open(filename, "w") as file:
     #Write the new data to the file
    file.write(str(x))


    file.close()