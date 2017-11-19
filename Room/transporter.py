#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr  3 20:16:49 2017

@author: coltrane
"""
#Are people passing inventory as 2 integers?
#gold then manna?
#I am assuming they are accessing this program from the command line
#am I supposed to access the room.cgi on their command line?

#you can use "import cgi" to parse cgi inputs - Edward (see slide 17 of lecture week 11 slides)

import sys
import subprocess
import urllib
import csv
import cgi

def AccessROOM(inventory,URL):

    #calling success program to update csv file
    print ("Content-type: text/html")
    print ("""
    <html>
        <form action="%s/success.py" method="post">
            You may enter the Blue Room <br/>
            Please update the occupation of your room <br/>
            <input type="hidden" name="inventory" value="%s">
            <input type="hidden" name="URL" value="http://cgi.cs.mcgill.ca/~htu6/Room">
            <input type="submit" value="Update">
        </form>
    </html> """ % (URL,inventory))

def RETURN(inventory,URL):
    #printing a form that accesses the refresh command on the webpage of the player
    print("Content-type: text/html")
    print ("""
    <html>
        <form action="%s/room.cgi" method="post">
            <input type="hidden" name="command" value="refresh">
            <input type="hidden" name="inventory" value="%s">
            The Blue Room is occupied <br/>
            Please return to your room <br/>
            <input type="submit" value="Return">
        </form>
    </html> """ % (URL,inventory))



def Accept(inventory,URL):

    int_list=[]
    #opening and reading the resources.csv file
    file1=open("./resources.csv","r")
    int_list=file1.read().split(',')
    int_list[2]=int_list[2].rstrip()
    #checking if room is occupied
    if(int_list[2]!="0"):
        RETURN(inventory,URL)
    else:
        AccessROOM(inventory,URL)

def main():
    #parsing cgi input
    form=cgi.FieldStorage()
    inventory=form["inventory"].value
    URL=form["URL"].value
    Accept(inventory,URL)

main()

