#ifdef VS_ARCADE_BOARD_CPP

void VSArcadeBoard::serialize(serializer& s) {
  s.integer(swap_controllers);
  s.integer(dip);
}

#endif
