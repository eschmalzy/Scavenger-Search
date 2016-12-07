#
#
#
our $aps =
[
 {
   name => 'Swampert',
   key  => 's',
   header => 'Swampert.h',
   cpp    => ['Swampert.cpp','State.cpp','cell.cpp','model.cpp', 'problem.cpp'],
   constructor => 'ems::Scavenger::Swampert(opts)',
 },
 {
   name => 'Manual',
   key  => 'm',
   header => 'Manual.h',
   cpp    => ['Manual.cpp'],
   constructor => 'ems::Scavenger::Manual()',
 },
#{
#  name => '',
#  key  => '',
#  header => '',
#  constructor => '',
#},
 ];

1;
