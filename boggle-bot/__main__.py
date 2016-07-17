"""Main entry point of boggle-bot."""
import sys

from wordplays import Wordplays

with Wordplays() as wp:
    try:
        if not wp.login(username='totally_human', password='qwerty123'):
            print('Username or password were incorrect.', file=sys.stderr)
            print('Exiting.', file=sys.stderr)
    except RuntimeError as e:
        print('Error:', e, file=sys.stderr)
        print('Exiting.', file=sys.stderr)
        sys.exit(1)

    print('Login successful.')
