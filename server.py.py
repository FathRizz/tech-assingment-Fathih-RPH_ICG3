from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/post-data', methods=['POST'])
def post_data():
    data = request.get_json()
    if 'sensor_value' in data:
        sensor_value = data['sensor_value']
        print(f"Received sensor value: {sensor_value}")
        response = {
            'status': 'success',
            'sensor_value': sensor_value
        }
        return jsonify(response), 200
    else:
        return jsonify({'status': 'error', 'message': 'Invalid data'}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
