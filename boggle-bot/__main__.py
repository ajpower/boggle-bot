"""Main entry point of boggle-bot."""
import getpass
import os
import sys
import time

from boggle import Boggle
from wordplays import Wordplays

MAX_CONSECUTIVE_ERRORS = 3

module_dir = os.path.dirname(__file__)
Boggle.load_dictionary(module_dir + '/dict.list')

username = input('Enter username: ')
password = getpass.getpass(prompt='Enter password: ')

with Wordplays() as wp:
    try:
        if not wp.login(username=username, password=password):
            print('Login unsuccessful.', file=sys.stderr)
            print('Exiting.', file=sys.stderr)
            sys.exit(1)
    except RuntimeError as e:
        print('Error:', e, file=sys.stderr)
        print('Exiting.', file=sys.stderr)
        sys.exit(1)

    print('Login successful.\n')

    # Continuously solve puzzles until too many consecutive errors are
    # encountered.
    consecutive_errors = 0
    n_puzzles = 0
    while consecutive_errors < MAX_CONSECUTIVE_ERRORS:
        try:
            boggle_elements = wp.start_boggle()
            b = Boggle(boggle_elements)
            words = b.solve()
            score, max_score = wp.solve(words)

            print('Puzzle number: {:5s}, score: {:>4s}, max score: {:>4s}'.
                  format(wp.pzlnbr, score, max_score))

            time.sleep(1)  # To avoid DOSing the server.
            consecutive_errors = 0
            n_puzzles += 1
        except Exception as e:
            print('Error:', e, file=sys.stderr)
            consecutive_errors += 1

    print('Too many consecutive errors were encountered. Exiting.',
          file=sys.stderr)
