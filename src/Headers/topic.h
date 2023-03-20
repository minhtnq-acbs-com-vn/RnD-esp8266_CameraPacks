#ifndef TOPIC_H
#define TOPIC_H

// Setup topic
// From device
inline const char *topicCameraPacksDevice = "640ee59066f4b889269ff405/CameraPack/room1";
inline const char *topicCameraPacksACK = "640ee59066f4b889269ff405/CameraPack/room1/ACK";
// To device
inline const char *topicCameraPacksServer = "640ee59066f4b889269ff405/CameraPack/room1/server";

inline String topic[] = {topicCameraPacksServer, topicCameraPacksACK, topicCameraPacksDevice};
inline String topicKey[] = {"subscribe", "ack", "publish"};

#endif