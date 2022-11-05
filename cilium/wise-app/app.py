from flask import Flask, jsonify
import os

app = Flask(__name__)

@app.route('/', methods=['GET'])
def overview():
    return 'Welcome to WISE! aka Western Intelligence\n'

@app.route('/report-mission', methods=['POST'])
def request_mission():
    return 'Handler (aka Sylvia): Keep up the goodwork agent Twilight. Until next time!\n'

@app.route('/emergency-abort', methods=['PUT'])
def emergency_abort():
    return 'ALERT! ALERT! ALERT!!!\nCODE: RED - STRATEGIC RETREAT!\nALL MISSIONS HAVE BEEN TERMINATED FORCEFULLY.\n'

if __name__ == "__main__":
    port = int(os.environ.get('PORT', 80))
    app.run(debug=False, host='0.0.0.0', port=port)
