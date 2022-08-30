;; Auto-generated. Do not edit!


(when (boundp 'fla_msgs::ImageSegmentation)
  (if (not (find-package "FLA_MSGS"))
    (make-package "FLA_MSGS"))
  (shadow 'ImageSegmentation (find-package "FLA_MSGS")))
(unless (find-package "FLA_MSGS::IMAGESEGMENTATION")
  (make-package "FLA_MSGS::IMAGESEGMENTATION"))

(in-package "ROS")
;;//! \htmlinclude ImageSegmentation.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass fla_msgs::ImageSegmentation
  :super ros::object
  :slots (_header _classes _height _width _data ))

(defmethod fla_msgs::ImageSegmentation
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:classes __classes) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:height __height) 0)
    ((:width __width) 0)
    ((:data __data) (make-array 0 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _header __header)
   (setq _classes __classes)
   (setq _height (round __height))
   (setq _width (round __width))
   (setq _data __data)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:classes
   (&optional __classes)
   (if __classes (setq _classes __classes)) _classes)
  (:height
   (&optional __height)
   (if __height (setq _height __height)) _height)
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; string[] _classes
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _classes)) 4
    ;; uint32 _height
    4
    ;; uint32 _width
    4
    ;; uint8[] _data
    (* 1    (length _data)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; string[] _classes
     (write-long (length _classes) s)
     (dolist (elem _classes)
       (write-long (length elem) s) (princ elem s)
       )
     ;; uint32 _height
       (write-long _height s)
     ;; uint32 _width
       (write-long _width s)
     ;; uint8[] _data
     (write-long (length _data) s)
     (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; string[] _classes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _classes (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _classes i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; uint32 _height
     (setq _height (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _width
     (setq _width (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8[] _data
   (let ((n (sys::peek buf ptr- :integer))) (incf ptr- 4)
     (setq _data (make-array n :element-type :char))
     (replace _data buf :start2 ptr-) (incf ptr- n))
   ;;
   self)
  )

(setf (get fla_msgs::ImageSegmentation :md5sum-) "878d061c51a3e50d80933aa4a4a33474")
(setf (get fla_msgs::ImageSegmentation :datatype-) "fla_msgs/ImageSegmentation")
(setf (get fla_msgs::ImageSegmentation :definition-)
      "Header header
string[] classes
uint32 height
uint32 width
uint8[] data
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



(provide :fla_msgs/ImageSegmentation "878d061c51a3e50d80933aa4a4a33474")


