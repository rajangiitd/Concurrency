from random import randint
import os
import time
import matplotlib.pyplot as plt

file = open('unique_words.txt', 'r')
data = file.read().strip().split('\n')

path1 = "/home/rajan/Desktop/COP290/COP_Lab2/Assignment2-COP290 updated/Assignment2-COP290/2018ME20710_2020CS10331_2020CS10409/part2/data"
path2 = "/home/rajan/Desktop/COP290/COP_Lab2/Assignment2-COP290 updated/Assignment2-COP290/2018ME20710_2020CS10331_2020CS10409/part3/data"


def generate_files(data, n):
    L = len(data)
    for i in range(2):
        file  = open( path1+"/in" + str(i+1) + '.txt', 'w')
        file1 = open( path2+"/in" + str(i+1) + '.txt', 'w')
        for j in range(6000//n):
            word_num = randint(0, L-1)
            for k in range(n):
                file.write(data[word_num]+'\n')
                file1.write(data[word_num]+'\n')
        file.close()
        file1.close()

# Count of files = n
Repetition_per_word = []
Time_taken_concurrency = []
Time_taken_parallelism = []

for i in range(100, 501, 100):
    generate_files(data, i)
    Repetition_per_word.append(i) # i -> repetition
    
    os.chdir(path1[:-4])
    start_time = time.time()
    os.system("make all")
    end_time = time.time()
    Time_taken = (end_time - start_time) ## time in seconds
    Time_taken_concurrency.append(Time_taken)
    
    os.chdir(path2[:-4])
    start_time = time.time()
    os.system("make test")
    end_time = time.time()
    Time_taken = (end_time - start_time) ## time in seconds
    Time_taken_parallelism.append(Time_taken)

print(Repetition_per_word)
print(Time_taken_concurrency)
print(Time_taken_parallelism)
## plot and save

plt.plot(Repetition_per_word, Time_taken_concurrency, 'r', label = "Concurrency")
plt.plot(Repetition_per_word, Time_taken_parallelism, 'b', label = "Parallelism")
plt.xlabel("Repetition_per_word")
plt.ylabel("Time (sec)")
plt.legend(loc="upper left")
plt.title("Performance of Concurrency vs Parallelism, with increasing repetitions[file count = 2]")
plt.savefig("Time_vs_Repetition_per_word.png")
plt.show()