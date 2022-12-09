import matplotlib.pyplot as plt
import csv
import math

def read_csv(fname, log10=False, clip=1000000000):
    dic = {}
    with open(fname) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        x=[]
        y=[]
        s=0
        for row in csv_reader:
            if (int)(row[0]) <= clip:
                dic[int(row[0])] = math.log10(int(row[1])) if log10 else int(row[1])
                s+=int(row[1])
        #Remove plotting zero degree
        if 0 in dic:
            del(dic[0])
        lists = sorted(dic.items())
        x,y = zip(*lists)
        plt.plot(x,y)

read_csv('outdeghis.csv')
plt.xlabel("Out Degree")
plt.ylabel("Number of nodes")
plt.savefig('Out_deg.png')
plt.clf()

read_csv('outdeghis.csv', log10=True)
plt.xlabel("Out Degree")
plt.ylabel("log10(Number of nodes)")
plt.savefig('Out_deg_log.png')
plt.clf()

read_csv('indeghis.csv', log10=True, clip=3000)
plt.xlabel("In Degree")
plt.ylabel("log10(Number of nodes)")
plt.savefig('In_deg_log.png')
plt.clf()

read_csv('deghis.csv', log10=True, clip=3000)
plt.xlabel("Degree")
plt.ylabel("log10(Number of nodes)")
plt.savefig('deg_log.png')
