#define CATCH_CONFIG_MAIN

#include "ConnectN.hpp"
#include "Visualizer.hpp"
#include "catch.hpp"

std::ostream& operator<<(std::ostream& os, GameStatuses const& value) {
  std::string result = std::to_string((int)value);

  if (value == GameStatuses::READY) {
    result = "Ready";
  } else if (value == GameStatuses::IN_GAME) {
    result = "In game";
  } else if (value == GameStatuses::YELLOW_WON) {
    result = "Yellow won!";
  } else if (value == GameStatuses::RED_WON) {
    result = "Red won!";
  } else if (value == GameStatuses::FULL_BOARD) {
    result = "Full board!";
  }

  os << result;
  return os;
}

SCENARIO(
    "When a player places four pieces in a vertical line, that player should"
    " win the game.", "[vert]") {
  GIVEN(
      "A board of the size of 7x7 and with four pieces in a row as the "
      "winning combination. This is the standard (\"Vanilla\") game option.") {
    ConnectN game(7, 7, 4);
    Visualizer v;

    WHEN("Test that four pieces stacked in column wins the game") {
      WHEN("The game starts.") {
        THEN(
            "Its status should be \"ready\" "
            "and the board should look like:\n" +
            v.print()) {
          REQUIRE(game.getCurrentStatus() == GameStatuses::READY);
        }

        WHEN(
            "Yellow and then red plays on the 1st and 2nd column "
            "respectively") {
          game.yellowPlays(1);
          game.redPlays(2);
          v.yellowPlays(1);
          v.redPlays(2);
          THEN(
              "The game status should be \"in game\" "
              "and the board should look like:\n" +
              v.print()) {
            REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
          }

          WHEN(
              "Yellow and then red plays on the 1st and 2nd column "
              "respectively") {
            game.yellowPlays(1);
            game.redPlays(2);
            v.yellowPlays(1);
            v.redPlays(2);
            THEN(
                "The game status should be \"in game\" "
                "and the board should look like:\n" +
                v.print()) {
              REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
            }

            WHEN(
                "Yellow and then red plays on the 1st and 2nd column "
                "respectively") {
              game.yellowPlays(1);
              game.redPlays(2);
              v.yellowPlays(1);
              v.redPlays(2);
              THEN(
                  "The game status should be \"in game\" "
                  "and the board should look like:\n" +
                  v.print()) {
                REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
              }

              WHEN("Yellow plays on the 1st column") {
                game.yellowPlays(1);
                v.yellowPlays(1);
                THEN(
                    "Yellow should win "
                    "and the board should look like:\n" +
                    v.print()) {
                  REQUIRE(game.getCurrentStatus() == GameStatuses::YELLOW_WON);
                }
              }
            }
          }
        }
      }
    }
  }
}
SCENARIO(
    "When a player places four pieces in a horizontal line, that player should "
    "win the game.", "[horiz]") {
  GIVEN(
      "A board of the size of 7x7 and with four pieces in a row as the "
      "winning combination. This is the standard (\"Vanilla\") game option.") {
    ConnectN game(7, 7, 4);
    Visualizer v;
    WHEN(
        "Test that four pieces placed along each other on one line wins the "
        "game") {
      WHEN("The game starts.") {
        THEN(
            "Its status should be \"ready\" "
            "and the board should look like:\n" +
            v.print()) {
          REQUIRE(game.getCurrentStatus() == GameStatuses::READY);
        }

        WHEN("Yellow and then red plays on the 1st column") {
          game.yellowPlays(1);
          game.redPlays(1);
          v.yellowPlays(1);
          v.redPlays(1);
          THEN(
              "The game status should be \"in game\" "
              "and the board should look like:\n" +
              v.print()) {
            REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
          }

          WHEN("Yellow and then red plays on the 2nd column") {
            game.yellowPlays(2);
            game.redPlays(2);
            v.yellowPlays(2);
            v.redPlays(2);
            THEN(
                "The game status should be \"in game\" "
                "and the board should look like:\n" +
                v.print()) {
              REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
            }

            WHEN("Yellow and then red plays on the 3rd column") {
              game.yellowPlays(3);
              game.redPlays(3);
              v.yellowPlays(3);
              v.redPlays(3);
              THEN(
                  "The game status should be \"in game\" "
                  "and the board should look like:\n" +
                  v.print()) {
                REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
              }

              WHEN("Yellow plays on the 4th column") {
                game.yellowPlays(3 + 1);
                v.yellowPlays(3 + 1);
                THEN(
                    "Yellow should win "
                    "and the board should look like:\n" +
                    v.print()) {
                  REQUIRE(game.getCurrentStatus() == GameStatuses::YELLOW_WON);
                }
              }
            }
          }
        }
      }
    }
  }
}

SCENARIO(
    "When a player places four pieces in a diagonal line, that player should "
    "win the game. Left to right", "[diag1]") {
  GIVEN(
      "A board of the size of 7x7 and with four pieces in a row as the "
      "winning combination. This is the standard (\"Vanilla\") game option.") {
    ConnectN game(7, 7, 4);
    Visualizer v;
    WHEN(
        "Test that four pieces are placed diagonally across the board wins the "
        "game") {
      WHEN("The game starts.") {
        THEN(
            "Its status should be \"ready\" "
            "and the board should look like:\n" +
            v.print()) {
          REQUIRE(game.getCurrentStatus() == GameStatuses::READY);
        }

        WHEN(
            "Yellow and then red plays on the 1st and 2nd column "
            "respectively") {
          game.yellowPlays(1);
          game.redPlays(2);
          v.yellowPlays(1);
          v.redPlays(2);
          THEN(
              "The game status should be \"in game\" "
              "and the board should look like:\n" +
              v.print()) {
            REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
          }

          WHEN(
              "Yellow and then red plays on the 2nd and 3rd column "
              "respectively") {
            game.yellowPlays(2);
            game.redPlays(3);
            v.yellowPlays(2);
            v.redPlays(3);
            THEN(
                "The game status should be \"in game\" "
                "and the board should look like:\n" +
                v.print()) {
              REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
            }

            WHEN(
                "Yellow and then red plays on the 3rd and 4th column "
                "respectively") {
              game.yellowPlays(3);
              game.redPlays(4);
              v.yellowPlays(3);
              v.redPlays(4);
              THEN(
                  "The game status should be \"in game\" "
                  "and the board should look like:\n" +
                  v.print()) {
                REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
              }

              WHEN(
                  "Yellow and then red plays on the 3rd and 4th column "
                  "respectively") {
                game.yellowPlays(3);
                game.redPlays(4);
                v.yellowPlays(3);
                v.redPlays(4);
                THEN(
                    "The game status should be \"in game\" "
                    "and the board should look like:\n" +
                    v.print()) {
                  REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
                }

                WHEN(
                    "Yellow and then red plays on the 4th and 6th column "
                    "respectively") {
                  game.yellowPlays(4);
                  game.redPlays(6);
                  v.yellowPlays(4);
                  v.redPlays(6);
                  THEN(
                      "The game status should be \"in game\" "
                      "and the board should look like:\n" +
                      v.print()) {
                    REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
                  }

                  WHEN("Yellow plays on the 4th column") {
                    game.yellowPlays(4);
                    v.yellowPlays(4);
                    THEN(
                        "Yellow should win "
                        "and the board should look like:\n" +
                        v.print()) {
                      REQUIRE(game.getCurrentStatus() ==
                              GameStatuses::YELLOW_WON);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

SCENARIO(
    "When a player places four pieces in a diagonal line, that player should "
    "win the game. Right to left", "[diag2]") {
  GIVEN(
      "A board of the size of 7x7 and with four pieces in a row as the "
      "winning combination. This is the standard (\"Vanilla\") game option.") {
    ConnectN game(7, 7, 4);
    Visualizer v;
    WHEN(
        "Test that four pieces are placed diagonally across the board wins the "
        "game") {
      WHEN("The game starts.") {
        THEN(
            "Its status should be \"ready\" "
            "and the board should look like:\n" +
            v.print()) {
          REQUIRE(game.getCurrentStatus() == GameStatuses::READY);
        }

        WHEN(
            "Yellow and then red plays on the 7st and 6nd column "
            "respectively") {
          game.yellowPlays(7);
          game.redPlays(6);
          v.yellowPlays(7);
          v.redPlays(6);
          THEN(
              "The game status should be \"in game\" "
              "and the board should look like:\n" +
              v.print()) {
            REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
          }

          WHEN(
              "Yellow and then red plays on the 6nd and 5rd column "
              "respectively") {
            game.yellowPlays(6);
            game.redPlays(5);
            v.yellowPlays(6);
            v.redPlays(5);
            THEN(
                "The game status should be \"in game\" "
                "and the board should look like:\n" +
                v.print()) {
              REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
            }

            WHEN(
                "Yellow and then red plays on the 5rd and 4th column "
                "respectively") {
              game.yellowPlays(5);
              game.redPlays(4);
              v.yellowPlays(5);
              v.redPlays(4);
              THEN(
                  "The game status should be \"in game\" "
                  "and the board should look like:\n" +
                  v.print()) {
                REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
              }

              WHEN(
                  "Yellow and then red plays on the 5rd and 4th column "
                  "respectively") {
                game.yellowPlays(5);
                game.redPlays(4);
                v.yellowPlays(5);
                v.redPlays(4);
                THEN(
                    "The game status should be \"in game\" "
                    "and the board should look like:\n" +
                    v.print()) {
                  REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
                }

                WHEN(
                    "Yellow and then red plays on the 4th and 2th column "
                    "respectively") {
                  game.yellowPlays(4);
                  game.redPlays(2);
                  v.yellowPlays(4);
                  v.redPlays(2);
                  THEN(
                      "The game status should be \"in game\" "
                      "and the board should look like:\n" +
                      v.print()) {
                    REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
                  }

                  WHEN("Yellow plays on the 4th column") {
                    game.yellowPlays(4);
                    v.yellowPlays(4);
                    THEN(
                        "Yellow should win "
                        "and the board should look like:\n" +
                        v.print()) {
                      REQUIRE(game.getCurrentStatus() ==
                              GameStatuses::YELLOW_WON);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

SCENARIO(
    "When one player connects two separate horizontal/vertical/diagonal lines, "
    "with a new piece, creating an even longer combined "
    "horizontal/vertical/diagonal line, that player should win the game.") {
  GIVEN(
      "A board of the size of 7x7 and with four pieces in a row as the winning "
      "combination. This is the standard (\"Vanilla\") game option.") {
    ConnectN game(7, 7, 4);
    Visualizer v;
    WHEN("The game starts.") {
      THEN(
          "Its status should be \"ready\" "
          "and the board should look like:\n" +
          v.print()) {
        REQUIRE(game.getCurrentStatus() == GameStatuses::READY);
      }

      WHEN("Yellow and then red plays on the 1st column") {
        game.yellowPlays(1);
        game.redPlays(1);
        v.yellowPlays(1);
        v.redPlays(1);
        THEN(
            "The game status should be \"in game\" "
            "and the board should look like:\n" +
            v.print()) {
          REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
        }

        WHEN("Yellow and then red plays on the 2nd column") {
          game.yellowPlays(2);
          game.redPlays(2);
          v.yellowPlays(2);
          v.redPlays(2);
          THEN(
              "The game status should be \"in game\" "
              "and the board should look like:\n" +
              v.print()) {
            REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
          }

          WHEN("Yellow and then red plays on the 4th column") {
            game.yellowPlays(4);
            game.redPlays(4);
            v.yellowPlays(4);
            v.redPlays(4);
            THEN(
                "The game status should be \"in game\" "
                "and the board should look like:\n" +
                v.print()) {
              REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
            }

            WHEN("Yellow and then red plays on the 5th column") {
              game.yellowPlays(5);
              game.redPlays(5);
              v.yellowPlays(5);
              v.redPlays(5);
              THEN(
                  "The game status should be \"in game\" "
                  "and the board should look like:\n" +
                  v.print()) {
                REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
              }

              WHEN("Yellow plays on the 3rd column") {
                game.yellowPlays(3);
                v.yellowPlays(3);
                THEN(
                    "Yellow should win "
                    "and the board should look like:\n" +
                    v.print()) {
                  REQUIRE(game.getCurrentStatus() == GameStatuses::YELLOW_WON);
                }
              }
            }
          }
        }
      }
    }
  }
}

SCENARIO(
    "When a column is full, it should not be possible to stack more pieces in "
    "that column") {
  GIVEN(
      "A board of the size of 5x3 and with four pieces in a row as the "
      "winning combination. This is a smaller game board than usual.") {
    ConnectN game(5, 3, 4);
    Visualizer v(5, 3);
    WHEN("The game starts.") {
      THEN(
          "Its status should be \"ready\" "
          "and the board should look like:\n" +
          v.print()) {
        REQUIRE(game.getCurrentStatus() == GameStatuses::READY);
      }
      WHEN(
          "Yellow and then red plays on the 1st and 2nd column respectively "
          "three times") {
        game.yellowPlays(1);
        game.redPlays(2);
        game.yellowPlays(1);
        game.redPlays(2);
        game.yellowPlays(1);
        game.redPlays(2);
        v.yellowPlays(1);
        v.redPlays(2);
        v.yellowPlays(1);
        v.redPlays(2);
        v.yellowPlays(1);
        v.redPlays(2);

        THEN(
            "The game status should be \"in game\" "
            "and the board should look like:\n" +
            v.print()) {
          REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
        }
        WHEN("Yellow plays on the 1st column") {
          bool status = game.yellowPlays(1);
          THEN(
              "Yellow should not be allowed to place another piece in that "
              "column "
              "and the board should look like:\n" +
              v.print()) {
            REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
            REQUIRE(status == false);
          }
          WHEN("Yellow plays on the 3rd column") {
            bool status = game.yellowPlays(3);
            v.yellowPlays(3);
            THEN(
                "Yellow should be allowed to place another piece in another "
                "column if the last try was outside of the board and therefore "
                "stopped"
                "and the board should look like:\n" +
                v.print()) {
              REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
              REQUIRE(status == true);
            }
          }
        }
      }
    }
  }
}

SCENARIO(
    "When someone has won. It should not be possible to place a new piece") {
  GIVEN(
      "A board of the size of 5x3 and with three pieces in a row as the "
      "winning combination. This is a smaller game board than usual.") {
    ConnectN game(5, 3, 3);
    Visualizer v(5, 3);
    WHEN("The game starts.") {
      THEN(
          "Its status should be \"ready\" "
          "and the board should look like:\n" +
          v.print()) {
        REQUIRE(game.getCurrentStatus() == GameStatuses::READY);
      }
      WHEN(
          "Red and then yellow plays on the 1st and 2nd column respectively "
          "two times") {
        game.redPlays(2);
        game.yellowPlays(1);
        game.redPlays(2);
        game.yellowPlays(1);
        v.redPlays(2);
        v.yellowPlays(1);
        v.redPlays(2);
        v.yellowPlays(1);

        THEN(
            "The game status should be \"in game\" "
            "and the board should look like:\n" +
            v.print()) {
          REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
        }
        WHEN("Red plays on the 2nd column") {
          bool status = game.redPlays(2);
          v.redPlays(2);
          THEN(
              "Red should win "
              "and the board should look like:\n" +
              v.print()) {
            REQUIRE(game.getCurrentStatus() == GameStatuses::RED_WON);
            REQUIRE(status == true);
          }
          WHEN("Yellow plays on the 3rd column") {
            bool status = game.yellowPlays(3);
            v.yellowPlays(3);
            THEN(
                "Yellow should not be allowed to place another piece if "
                "someone has won the game"
                "and the board should look like:\n" +
                v.print()) {
              REQUIRE(game.getCurrentStatus() == GameStatuses::RED_WON);
              REQUIRE(status == false);
            }
          }
        }
      }
    }
  }
}
SCENARIO("It should not be possible to place a piece outside of the board") {
  GIVEN(
      "A board of the size of 5x3 and with four pieces in a row as the "
      "winning combination. This is a smaller game board than usual.") {
    ConnectN game(5, 3, 4);
    Visualizer v(5, 3);
    WHEN("The game starts.") {
      THEN(
          "Its status should be \"ready\" "
          "and the board should look like:\n" +
          v.print()) {
        REQUIRE(game.getCurrentStatus() == GameStatuses::READY);
      }
      WHEN("Yellow plays on the 10th column") {
        bool status = game.yellowPlays(10);
        THEN(
            "Yellow should not be allowed to place a piece outside of the "
            "board "
            "and the board should look like:\n" +
            v.print()) {
          REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
          REQUIRE(status == false);
        }
        WHEN("Yellow plays on the 3rd column") {
          bool status = game.yellowPlays(3);
          v.yellowPlays(3);
          THEN(
              "Yellow should be allowed to place a piece in another "
              "column if the last try was outside of the board and therefore "
              "stopped"
              "and the board should look like:\n" +
              v.print()) {
            REQUIRE(game.getCurrentStatus() == GameStatuses::IN_GAME);
            REQUIRE(status == true);
          }
        }
      }
    }
  }
}