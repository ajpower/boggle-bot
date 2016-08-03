"""This module provides a Wordplays object to interact with wordplays.com."""
import requests
import time

from bs4 import BeautifulSoup

LOGIN_URL = 'http://www.wordplays.com/wordgames/signin.pl'
BOGGLE_URL = 'http://www.wordplays.com/boggle'


class Wordplays:
    """A wordplays.com session.

    Provides methods for interacting with wordplays.com, including logging in
    and starting a boggle game. Has methods for context management, so can (and
    should) be called with the with statement.
    """

    def __init__(self):
        # Keep track of current puzzle number and puzzle key.
        self.pzlnbr = ''
        self.pzlkey = ''


        # Session object to handle cookie persistence etc.
        self._session = requests.Session()
        # Header data to mimic browser.
        self._headers = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) '
                                       'AppleWebKit/537.36 (KHTML, like Gecko) '
                                       'Chrome/52.0.2743.82 Safari/537.36'}

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self._session.__exit__(*args)

    def login(self, username, password):
        """Attempt to log in to wordplays.com and return True if successful.

        Raise a RuntimeError if login attempt cannot be made.

        :param username: Account username.
        :param password: Account password.
        :return: True if login was successful.
        """
        payload = {'userid': username, 'pwd': password, 'signin': 'Sign In'}

        try:
            s = self._session.post(url=LOGIN_URL, data=payload,
                                   headers=self._headers)
        except requests.RequestException as e:
            raise RuntimeError(e) from e

        # If login was successful, the resulting HTML will contain a div with
        # id=signed-in.
        soup = BeautifulSoup(markup=s.text, features='lxml')
        return soup.find('div', attrs={'id': 'signed-in'}) is not None

    def start_boggle(self):
        """Play a boggle game, record the puzzle number and ket, and return the
        boggle board.

        Raise a RuntimeError if boggle game cannot be started.

        :return List of characters in the Boggle board.
        """
        try:
            s = self._session.get(BOGGLE_URL, headers=self._headers)
        except requests.RequestException as e:
            raise RuntimeError(e) from e

        # Collect boggle elements, puzzle number, and puzzle key.
        soup = BeautifulSoup(markup=s.text, features='lxml')
        boggle_table = soup.find('table', attrs={'id': 'pzl'})
        boggle_elements = [boggle_element.find('input')['value'] for
                           boggle_element in boggle_table.find_all('td')]
        self.pzlnbr = soup.find('input', attrs={'name': 'pzlnbr'})['value']
        self.pzlkey = soup.find('input', attrs={'name': 'pzlkey'})['value']

        return boggle_elements

    def solve(self, words):
        """Send the given words as a solution to the current boggle game.

        Raise a RuntimeError if words cannot be sent to the server.

        :param words: Solutions to the current Boggle game.
        :return Tuple containing actual score and max score.
        """
        payload = {'answers': '\n'.join(words),
                   'op': 'solve',
                   'pzlnbr': self.pzlnbr,
                   'pzlkey': self.pzlkey,
                   'pzltype': 'F',
                   'ax': 0,
                   'clock': '2:59',
                   'gametime': int(time.time())}

        try:
            s = self._session.post(url=BOGGLE_URL, data=payload,
                                   headers=self._headers)
        except requests.RequestException as e:
            raise RuntimeError(e) from e

        # Get score and max score.
        soup = BeautifulSoup(markup=s.text, features='lxml')
        score_table = soup.find('table', attrs={'id': 'score-table'})
        score = score_table.find_all('td')[0].text
        max_score = score_table.find_all('td')[1].text

        return score, max_score
