from flask import Flask, render_template, request, jsonify,redirect, url_for
from flask_socketio import SocketIO, send, emit

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

global text

@app.route('/text')
def wemos():
	global text
	text_r = text
	return text_r

@app.route('/formin',methods=['GET',"POST"])
def forms():
	global text
	if request.method == 'POST':
		text = request.form['text']
		print(text)
		#return redirect(url_for('form'))
		return render_template('formin.html')
	else:
		print("ELSE")
		#return redirect(url_for('form'))
		return render_template('formin.html')