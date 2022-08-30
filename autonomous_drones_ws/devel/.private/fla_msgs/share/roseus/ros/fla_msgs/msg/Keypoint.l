;; Auto-generated. Do not edit!


(when (boundp 'fla_msgs::Keypoint)
  (if (not (find-package "FLA_MSGS"))
    (make-package "FLA_MSGS"))
  (shadow 'Keypoint (find-package "FLA_MSGS")))
(unless (find-package "FLA_MSGS::KEYPOINT")
  (make-package "FLA_MSGS::KEYPOINT"))

(in-package "ROS")
;;//! \htmlinclude Keypoint.msg.html


(defclass fla_msgs::Keypoint
  :super ros::object
  :slots (_id _x _y ))

(defmethod fla_msgs::Keypoint
  (:init
   (&key
    ((:id __id) 0)
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _x (float __x))
   (setq _y (float __y))
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:serialization-length
   ()
   (+
    ;; uint32 _id
    4
    ;; float32 _x
    4
    ;; float32 _y
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _id
       (write-long _id s)
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get fla_msgs::Keypoint :md5sum-) "b8a73f27507e9626faa0d25bacb6ecf2")
(setf (get fla_msgs::Keypoint :datatype-) "fla_msgs/Keypoint")
(setf (get fla_msgs::Keypoint :definition-)
      "# (x, y) define the keypoint location in pixel coordinates
uint32 id
float32 x 
float32 y

")



(provide :fla_msgs/Keypoint "b8a73f27507e9626faa0d25bacb6ecf2")


