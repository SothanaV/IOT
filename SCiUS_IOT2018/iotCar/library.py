import http.client
from time import sleep

url = "192.168.1.12"

def request(path):
	connection = http.client.HTTPConnection(url)
	connection.request("GET",path)
	response = connection.getresponse()
	data = response.read().decode("utf-8") 
	connection.close()
	#print("Request to "+url+path)
	return data

class Motor:
	def forward(self,delay):
		request("/go?method=forward&delay="+str(delay))
	def backward(self,delay):
		request("/go?method=backward&delay="+str(delay))
	def left(self,delay):
		request("/go?method=left&delay="+str(delay))
	def right(self,delay):
		request("/go?method=right&delay="+str(delay))
motor = Motor()

def led(r,g,b):
	request("/led?r="+str(r)+"&g="+str(g)+"&b="+str(b))

def temp():
	data = request('/dht')
	data = data.split(',')
	return data[0]

def humi():
	data = request('/dht')
	data = data.split(',')
	return data[1]

Melody = {
'B0':31	,
'C1':33	,
'CS1':35	,
'D1':37	,
'DS1':39	,
'E1':41	,
'F1':44	,
'FS1':46	,
'G1':49	,
'GS1':52	,
'A1':55	,
'AS1':58	,
'B1':62	,
'C2':65	,
'CS2':69	,
'D2':73	,
'DS2':78	,
'E2':82	,
'F2':87	,
'FS2':93	,
'G2':98	,
'GS2':104	,
'A2':110	,
'AS2':117	,
'B2':123	,
'C3':131	,
'CS3':139	,
'D3':147	,
'DS3':156	,
'E3':165	,
'F3':175	,
'FS3':185	,
'G3':196	,
'GS3':208	,
'A3':220	,
'AS3':233	,
'B3':247	,
'C4':262	,
'CS4':277	,
'D4':294	,
'DS4':311	,
'E4':330	,
'F4':349	,
'FS4':370	,
'G4':392	,
'GS4':415	,
'A4':440	,
'AS4':466	,
'B4':494	,
'C5':523	,
'CS5':554	,
'D5':587	,
'DS5':622	,
'E5':659	,
'F5':698	,
'FS5':740	,
'G5':784	,
'GS5':831	,
'A5':880	,
'AS5':932	,
'B5':988	,
'C6':1047	,
'CS6':1109 ,
'D6':1175  ,
'DS6':1245 ,
'E6':1319  ,
'F6':1397  ,
'FS6':1480 ,
'G6':1568  ,
'GS6':1661 ,
'A6':1760  ,
'AS6':1865 ,
'B6':1976  ,
'C7':2093  ,
'CS7':2217 ,
'D7':2349  ,
'DS7':2489 ,
'E7':2637  ,
'F7':2794  ,
'FS7':2960 ,
'G7':3136  ,
'GS7':3322 ,
'A7':3520  ,
'AS7':3729 ,
'B7':3951  ,
'C8':4186  ,
'CS8':4435 ,
'D8':4699  ,
'DS8':4978 ,
'0':0, }

def sound(melody,duration):
	#print('/sound?melody='+str(Melody[melody])+'&duration='+str(duration))
	
	request('/sound?melody='+str(Melody[melody])+'&duration='+str(duration))