#include "BluetoothA2DPSink.h"
#include "AudioGeneratorTalkie.h"
#include "AudioOutputSPDIF.h"
#include <AudioGeneratorFLAC.h>
#include <AudioFileSourcePROGMEM.h>

BluetoothA2DPSink a2dp_sink;
AudioOutputSPDIF *output = NULL;
AudioGeneratorFLAC *flac;
AudioFileSourcePROGMEM *file;

#define SPI_SPEED SD_SCK_MHZ(40)
#define SPDIF_OUT_PIN 27

void setup() {
  Serial.begin(115200);
  Serial.println("Start.");
  audioLogger = &Serial;  
  audioLogger->println(F("Started audioLogger"));
  a2dp_sink.set_stream_reader(read_data_stream);
  a2dp_sink.start("MyESP");
  Serial.println("Started bluetooth.");
  output = new AudioOutputSPDIF(SPDIF_OUT_PIN);  
  Serial.println("Started AudioOutputSPDIF.");
}

// Then somewhere in your sketch:
void read_data_stream(const uint8_t *data, uint32_t length)
{
  Serial.print(length);
  Serial.println(" bytes.");
  file = new AudioFileSourcePROGMEM( data, length);
  Serial.println("AudioFileSourcePROGMEM");
  flac = new AudioGeneratorFLAC();
  Serial.println("AudioGeneratorFLAC");
  flac->begin(file, output);
  Serial.println("begin");
  flac->loop();
  Serial.println("flac->loop ended");
}

void loop() {
  
}
