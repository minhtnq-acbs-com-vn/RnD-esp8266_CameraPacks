#ifndef TOPIC_H
#define TOPIC_H

// Setup topic
// From device
inline const char *topicCameraPacksDevice = "CameraPack/room1";
inline const char *topicCameraPacksACK = "CameraPack/room1/ACK";
// To device
inline const char *topicCameraPacksServer = "CameraPack/room1/server";

inline String topic[] = {topicCameraPacksDevice, topicCameraPacksACK, topicCameraPacksServer};
inline String topicKey[] = {"subscribe", "ack", "publish"};

#endif