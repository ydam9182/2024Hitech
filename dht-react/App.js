import React, { useState } from 'react';
import axios from 'axios';

function App(){
        const [sensorData, setSensorData] = useState({temp: null, humi: null});
        const [state, setState] = useState(false);

        const handleButtonClick = () => {
            axios.get('http://localhost:3001/api/data')
            .then(response => {
                    setSensorData(response.data);
            })
            .catch(error => {
                    console.error('Error fetching sensor data:', error);
            });
        };

        const handleStateChange = () => {
            axios.post('http://localhost:3001/api/state')
                .then(response => {
                        setState(!state);
                        console.log('State changed:', !state);
                })
            .catch(error => {
                    console.error('Error changing state :', error);
            });
        };

        return (
            <div>
                <h1> temperture and Humility </h1>
                <button onClick={handleButtonClick}>Get dataes</button>
                <button onClick={handleStateChange}>Change State</button>
                <p> temp : {sensorData.temp}c</p>
                <p> humi : {sensorData.humi}%</p>
                    <p> state : {state ? "On" : "Off"}</p>
           </div>
        );
};

export default App;
