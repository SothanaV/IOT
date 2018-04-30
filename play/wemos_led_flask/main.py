from flask import Flask, render_template, request, jsonify
from flask_socketio import SocketIO, send, emit
from datetime import datetime,timedelta
import json
#from StringIO import StringIO
from io import StringIO
import sqlite3
##Target is Data from Browser to set Humidity,Temperature 
##State  is Data From Client(Wemos) to get Humidity,Temperature
from time import sleep
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)
##Defind Start Value##
targetH = 0
targetT = 0
switchT = '100'
switchH = '200'
Red = 0
Green = 0
Blue = 0
io = StringIO()
stateT = 0
stateH = 0
L_status = "ON"
commandClick = 1
#Get data From Browser	
@socketio.on('c2s')																				#listen Data From Browser parth socketio "c2s" = cilent to server 
def C2S(data):
	global targetT
	global targetH
	global Red
	global Green
	global Blue
	sdata=json.loads(data)																		#get DAta By JsonFile
	targetT = float(sdata['T'])																	#sprit data 															
	targetH = float(sdata['H'])
	Red = float(sdata['R'])
	Green = float(sdata['G'])
	Blue = float(sdata['B'])
	'''
	IRF540N
	'''
	Red = 999 - Red
	Green = 999 - Green
	Blue = 999 - Blue
	####################
	# print ("TARGET_T : %s"%(targetT))																#print data
	# print ("TARGET_H : %s"%(targetH))
	print ("Red%03d,Green%03d,Blue%03d"%(Red,Green,Blue))
	status = {
		'r' : Red,
		'g' : Green,
		'b' : Blue,
		'tT' : targetT,
		'tH' : targetH,
	}
	socketio.emit('status',status)

@app.route("/data/<t>/<h>")																			#Get data From Client(Wemos)
def alarm(t,h):
	global Red
	global Green
	global Blue
	global stateT,stateH, last_writedb 
	stateT = t
	stateH = h
	return "%s,%s,%03d,%03d,%03d"%(switchT,switchH,Red,Green,Blue)

@app.route("/led")
def ad():
	global stateT,stateH,targetT,targetH,Red,Green,Blue
	context = { 
		'r' : Red,
		'g' : Green,
		'b' : Blue,
		'sT' : stateT,
		'sH' : stateH,
		'tT' : targetT,
		'tH' : targetH,
	}
	return render_template('led.html',context=context)

if __name__ == "__main__":
    #app.run(host='0.0.0.0',port=4999,debug=True)
    socketio.run(app)


