"""Main entry point of boggle-bot."""
import sys

from boggle import Boggle
from wordplays import Wordplays

Boggle.load_dictionary('dict.list')

with Wordplays() as wp:
    try:
        if not wp.login(username='totally_human', password='qwerty123'):
            print('Login unsuccessful.', file=sys.stderr)
            print('Exiting.', file=sys.stderr)
            sys.exit(1)
    except RuntimeError as e:
        print('Error:', e, file=sys.stderr)
        print('Exiting.', file=sys.stderr)
        sys.exit(1)

    print('Login successful.')

    boggle_elements = wp.start_boggle()
    b = Boggle(boggle_elements)
    words = b.solve()
    score, max_score = wp.solve(words)
    print(score, max_score)
