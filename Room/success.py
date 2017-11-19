#!/usr/bin/env python3
import sys
import csv
import cgi

def main():
	form=cgi.FieldStorage()
	inventory=form["inventory"].value
	URL=form["URL"].value #getting URL of their room

	int_list=[]
	file1=open("./resources.csv", "r")
    #parsing the contents of resources.csv and writing them into a list
	int_list=file1.read().split(',')
	int_list[2]=int_list[2].rstrip()
	int_list[0]=str(int(int_list[0]) - 1)
	file1.close()

	file2=open("./resources.csv","w").close() #empty csv file

	file3=open("./resources.csv","w") #write to csv file
	file3writer = csv.writer(file3, delimiter=' ',quotechar='|', quoting=csv.QUOTE_MINIMAL)
	file3writer.writerow([int_list[0]+","+int_list[1]+","+"0"]) #replacing the occupied status with 0
	file3.close()

	print ("Content-type: text/html\n\n")
	print ("""
    <html>
        <form action="%s/room.cgi" method="post">
            <input type="hidden" name="command" value="refresh">
            <input type="hidden" name="inventory" value="%s">
            You may proceed to the next room.<br/>
            <input type="submit" value="Go">
        </form>
    </html> """ % (URL,inventory))

main()

