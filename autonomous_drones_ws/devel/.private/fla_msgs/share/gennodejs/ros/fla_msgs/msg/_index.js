
"use strict";

let FlightCommand = require('./FlightCommand.js');
let ImageSegmentation = require('./ImageSegmentation.js');
let JoyDef = require('./JoyDef.js');
let Keypoint = require('./Keypoint.js');
let ProcessStatus = require('./ProcessStatus.js');
let TelemString = require('./TelemString.js');
let FlightStateTransition = require('./FlightStateTransition.js');
let ImageDetections = require('./ImageDetections.js');
let NodeList = require('./NodeList.js');
let WaypointList = require('./WaypointList.js');
let Box = require('./Box.js');
let NodeStatus = require('./NodeStatus.js');
let Latency = require('./Latency.js');
let FlightEvent = require('./FlightEvent.js');
let Detection = require('./Detection.js');
let ControlMessage = require('./ControlMessage.js');

module.exports = {
  FlightCommand: FlightCommand,
  ImageSegmentation: ImageSegmentation,
  JoyDef: JoyDef,
  Keypoint: Keypoint,
  ProcessStatus: ProcessStatus,
  TelemString: TelemString,
  FlightStateTransition: FlightStateTransition,
  ImageDetections: ImageDetections,
  NodeList: NodeList,
  WaypointList: WaypointList,
  Box: Box,
  NodeStatus: NodeStatus,
  Latency: Latency,
  FlightEvent: FlightEvent,
  Detection: Detection,
  ControlMessage: ControlMessage,
};
