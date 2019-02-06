import csv

with open('output.tsv') as tsvfile:
    reader = csv.DictReader(tsvfile, dialect='excel-tab')
    print("x\ty\tz\tid")
    for row in reader:
        #print(row)
        x = ((float(row['min_lon']) + float(row['max_lon']) + 180.0) / 2.0) - 180.0
        y = ((float(row['min_lat']) + float(row['max_lat']) + 90.0) / 2.0) - 90.0          
        print("{}\t{}\t{}\t{}".format(x, y, row['created_at'], row['id']))
        

