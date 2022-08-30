# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from fla_msgs/NodeStatus.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class NodeStatus(genpy.Message):
  _md5sum = "bc0e9b8f7a292a18c6b50b43586a86d8"
  _type = "fla_msgs/NodeStatus"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """uint8 INACTIVE=1
uint8 STARTING=2
uint8 INIT=3
uint8 READY=4
uint8 ALARM=5
uint8 FAIL=6
uint8 SILENT=7
uint32 id
uint32 pid
uint8 status
int32 arg
float64 load
"""
  # Pseudo-constants
  INACTIVE = 1
  STARTING = 2
  INIT = 3
  READY = 4
  ALARM = 5
  FAIL = 6
  SILENT = 7

  __slots__ = ['id','pid','status','arg','load']
  _slot_types = ['uint32','uint32','uint8','int32','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       id,pid,status,arg,load

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(NodeStatus, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.id is None:
        self.id = 0
      if self.pid is None:
        self.pid = 0
      if self.status is None:
        self.status = 0
      if self.arg is None:
        self.arg = 0
      if self.load is None:
        self.load = 0.
    else:
      self.id = 0
      self.pid = 0
      self.status = 0
      self.arg = 0
      self.load = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_2IBid().pack(_x.id, _x.pid, _x.status, _x.arg, _x.load))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 21
      (_x.id, _x.pid, _x.status, _x.arg, _x.load,) = _get_struct_2IBid().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_2IBid().pack(_x.id, _x.pid, _x.status, _x.arg, _x.load))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 21
      (_x.id, _x.pid, _x.status, _x.arg, _x.load,) = _get_struct_2IBid().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2IBid = None
def _get_struct_2IBid():
    global _struct_2IBid
    if _struct_2IBid is None:
        _struct_2IBid = struct.Struct("<2IBid")
    return _struct_2IBid
