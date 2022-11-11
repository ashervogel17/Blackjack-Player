# Blackjack Player

This program uses the client-side of the networking module and reinforcement learning via the decisionmaker wrapper for hashtable to development a blackjack strategy.

## Assumptions

The only assumption for this module is that the server it connects to has the same understanding of the protocols and thus sends the message we are expecting. This module has minimal handling of erroneous messages.

## Testing

To test the decisionmaker struct, use the command: `mygcc -o decisionmaker_test decisionmaker.c ../libcs50/libcs50-given.a -I../libcs50 -DUNITTEST` and run the program with `myvalgrind ./decisionmaker_test`.

The best way to test the player program is to connect to the dealer server with valgrind.