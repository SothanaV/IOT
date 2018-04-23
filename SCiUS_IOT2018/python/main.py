from flask import Flask,render_template,request
from flask_socketio import SocketIO, send, emit
from pitch import pitch
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)
@app.route('/')
def test():
	print("Def Test")
	return 'H W Naii'

@app.route('/data/<t>/<h>/')
def recieveDeta(t,h):
	print(("Temp%s,Humi%s")%(t,h))
	command = GetCommand()
	return command
@app.route('/note')
def getnote():
	x = 'C1'
	note = pitch(x)
	return note
	
def GetCommand():
	led_r = 1
	led_g = 2
	led_b = 3
	note =  4
	motor_lf = 5
	motor_lr = 6
	motor_rf = 7
	motor_rr = 8
	command = "%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d "%(led_r,led_g,led_b,note,motor_lf,motor_lr,motor_rf,motor_rr)
	print(command)
	return command

@app.route('/control')
def RenderTemplates():
	return render_template('control.html')
# @socketio.on('R')
# def get_R(R):
# 	print("Red"+R)
# 	return R
# @socketio.on('G')
# def get_G(G):
# 	print("Green"+G)
# 	return G
# @socketio.on('B')
# def get_B(B):
# 	print("Blue"+B)
# 	return B
# def getdata():
# 	red = socketio.on('R')
# 	red = int(red)
# 	return red
if __name__ == "__main__":
	# app.run(host='0.0.0.0',port=5000,debug=True)
    socketio.run(app)