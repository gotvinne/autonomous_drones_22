;; Auto-generated. Do not edit!


(when (boundp 'fla_msgs::ProcessStatus)
  (if (not (find-package "FLA_MSGS"))
    (make-package "FLA_MSGS"))
  (shadow 'ProcessStatus (find-package "FLA_MSGS")))
(unless (find-package "FLA_MSGS::PROCESSSTATUS")
  (make-package "FLA_MSGS::PROCESSSTATUS"))

(in-package "ROS")
;;//! \htmlinclude ProcessStatus.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(intern "*INIT*" (find-package "FLA_MSGS::PROCESSSTATUS"))
(shadow '*INIT* (find-package "FLA_MSGS::PROCESSSTATUS"))
(defconstant fla_msgs::ProcessStatus::*INIT* 3)
(intern "*READY*" (find-package "FLA_MSGS::PROCESSSTATUS"))
(shadow '*READY* (find-package "FLA_MSGS::PROCESSSTATUS"))
(defconstant fla_msgs::ProcessStatus::*READY* 4)
(intern "*ALARM*" (find-package "FLA_MSGS::PROCESSSTATUS"))
(shadow '*ALARM* (find-package "FLA_MSGS::PROCESSSTATUS"))
(defconstant fla_msgs::ProcessStatus::*ALARM* 5)
(intern "*FAIL*" (find-package "FLA_MSGS::PROCESSSTATUS"))
(shadow '*FAIL* (find-package "FLA_MSGS::PROCESSSTATUS"))
(defconstant fla_msgs::ProcessStatus::*FAIL* 6)

(defun fla_msgs::ProcessStatus-to-symbol (const)
  (cond
        ((= const 3) 'fla_msgs::ProcessStatus::*INIT*)
        ((= const 4) 'fla_msgs::ProcessStatus::*READY*)
        ((= const 5) 'fla_msgs::ProcessStatus::*ALARM*)
        ((= const 6) 'fla_msgs::ProcessStatus::*FAIL*)
        (t nil)))

(defclass fla_msgs::ProcessStatus
  :super ros::object
  :slots (_header _pid _name _hostname _status _message ))

(defmethod fla_msgs::ProcessStatus
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pid __pid) 0)
    ((:name __name) "")
    ((:hostname __hostname) "")
    ((:status __status) 0)
    ((:message __message) "")
    )
   (send-super :init)
   (setq _header __header)
   (setq _pid (round __pid))
   (setq _name (string __name))
   (setq _hostname (string __hostname))
   (setq _status (round __status))
   (setq _message (string __message))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pid
   (&optional __pid)
   (if __pid (setq _pid __pid)) _pid)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:hostname
   (&optional __hostname)
   (if __hostname (setq _hostname __hostname)) _hostname)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:message
   (&optional __message)
   (if __message (setq _message __message)) _message)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint32 _pid
    4
    ;; string _name
    4 (length _name)
    ;; string _hostname
    4 (length _hostname)
    ;; uint8 _status
    1
    ;; string _message
    4 (length _message)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint32 _pid
       (write-long _pid s)
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; string _hostname
       (write-long (length _hostname) s) (princ _hostname s)
     ;; uint8 _status
       (write-byte _status s)
     ;; string _message
       (write-long (length _message) s) (princ _message s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint32 _pid
     (setq _pid (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _hostname
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _hostname (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; uint8 _status
     (setq _status (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; string _message
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get fla_msgs::ProcessStatus :md5sum-) "deda7773ae20bf2b053b7c147297cf13")
(setf (get fla_msgs::ProcessStatus :datatype-) "fla_msgs/ProcessStatus")
(setf (get fla_msgs::ProcessStatus :definition-)
      "Header header
uint32 pid
string name
string hostname
uint8 status
string message

uint8 INIT=3
uint8 READY=4
uint8 ALARM=5
uint8 FAIL=6
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :fla_msgs/ProcessStatus "deda7773ae20bf2b053b7c147297cf13")


