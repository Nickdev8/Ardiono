<?php
header('Access-Control-Allow-Origin: *');

$json = file_get_contents('php://input');

if (empty($json)) {
    $json = file_get_contents("jsonInput.json");
    echo $json;
} else {
    if (strlen($json) > 1024) {
        http_response_code(400);
        echo json_encode(["error" => "Data is over 1024 characters!"]);
        exit;
    }

    // Decode the JSON input
    $data = json_decode($json);
    if ($data === null) {
        http_response_code(400);
        echo json_encode(["error" => "Invalid JSON input"]);
        exit;
    }

    // Read the existing JSON file
    $fileContents = file_get_contents("jsonInput.json");
    $fileData = json_decode($fileContents);

    // Update the file data with the new input
    if (isset($data->ldr)) {
        $fileData->ldr = $data->ldr;
    }
    if (isset($data->dht11)) {
        if (isset($data->dht11->temperature)) {
            $fileData->dht11->temperature = $data->dht11->temperature;
        }
        if (isset($data->dht11->humidity)) {
            $fileData->dht11->humidity = $data->dht11->humidity;
        }
        if (isset($data->dht11->heatIndex)) {
            $fileData->dht11->heatIndex = $data->dht11->heatIndex;
        }
    }

    // Control lights based on sensor data
    $fileData->lights = [
        "LED1" => ($fileData->ldr < 600) ? 1 : 0,                             // if light is low (LDR < 500)
        "LED2" => ($fileData->ldr >= 600 && $fileData->ldr <= 900) ? 1 : 0,   // if light is average (500 <= LDR <= 900)
        "LED3" => ($fileData->dht11->temperature > 20) ? 1 : 0                // if temperature > 20°C
    ];

    $jsonFile = fopen("jsonInput.json", "w");
    fwrite($jsonFile, json_encode($fileData));
    fclose($jsonFile);

    header('Content-Type: application/json; charset=UTF-8');
    echo json_encode($fileData);
}
?>