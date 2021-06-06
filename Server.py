import flask
import requests


#Google Maps Places API to get Coordinates
key='AIzaSyATVZ5GJHfpleI_VpviC6BSGQcIepeYpXI'


# FOR IP AND PORT SETTINGS, TAKE A LOOK AT THE END OF THE SCRIPT


#Configuration
app = flask.Flask(__name__)
app.config["DEBUG"] = True

#Request Handling
@app.route('/flyto/<place>', methods=['GET']) #IndexPage
def flyto(place):
    r=requests.get('https://maps.googleapis.com/maps/api/place/findplacefromtext/json?input='+place+'&fields=name,geometry&inputtype=textquery&key='+key)
    data=r.json()
    lat = str(data['candidates'][0]['geometry']['location']['lat'])
    lon = str(data['candidates'][0]['geometry']['location']['lng'])
    requests.get('http://localhost:5430/kml/flyto/%s/%s/40000'%(lon,lat))

    return "<h1>Flying to %s</h1><p>Message received and processed successfully.</p>"% place

#CHANGE THESE VALUES
app.run(host="<enter master ip>", port="8005")
