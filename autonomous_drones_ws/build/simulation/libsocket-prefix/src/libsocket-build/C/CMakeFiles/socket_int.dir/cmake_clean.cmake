file(REMOVE_RECURSE
  "libsocket_int.a"
  "libsocket_int.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/socket_int.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
