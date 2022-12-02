import boto3, io, json
from flask import Flask
from flask import request
from flask import jsonify
from werkzeug.serving import WSGIRequestHandler
WSGIRequestHandler.protocol_version = "HTTP/1.1"

app = Flask(__name__)

file_name="weather_db.txt"   # Download from Icampus
bucket_name="zappa-0aikw478u"  # Your bucket name
file_key="weather_db.txt"    # Same with file name

@app.route("/upload", methods=['GET'])
def upload():
    global file_name, bucket_name, file_key
    
    s3 = boto3.client("s3")

    # case 1 : upload your local file
    s3.upload_file(
	    Filename=file_name,
	    Bucket=bucket_name,
	    Key=file_key,
    )

    # case 2 : upload new file by stringIO body
    contents="My string to save to s3 object"
    fake_handle=io.StringIO(contents)
    s3.put_object(Bucket=bucket_name, Key="stringIO_test.txt", Body=fake_handle.read())

    print("upload finish")
    return jsonify("upload finish")

@app.route("/access", methods=['GET'])
def access_dat():
    global file_name, bucket_name, file_key
     
    name=request.args.get('name')    # Input name for searching region
    
    s3 = boto3.client("s3")
    obj=s3.get_object(
	    Bucket=bucket_name,
	    Key=file_key,
        )

    file_data=io.BytesIO(obj["Body"].read())
    
    region="Search failed"
    for byte_line in file_data:
        line=byte_line.decode().rstrip()
        line_arr=line.split(' ')
        if line_arr[0]==name:
            region=line_arr[1]
            
    return jsonify(region), 200

if __name__ == "__main__":
    app.run(host='localhost', port=8888)