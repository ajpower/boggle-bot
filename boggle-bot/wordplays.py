"""This module provides a Wordplays object to interact with wordplays.com."""
import requests

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
        # Session object to handle cookie persistence etc.
        self._session = requests.Session()

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
            s = self._session.post(url=LOGIN_URL, data=payload)
        except requests.RequestException as e:
            raise RuntimeError(e) from e

        # If login was successful, the resulting HTML will contain a div with
        # id=signed-in.
        soup = BeautifulSoup(markup=s.text, features='lxml')
        return soup.find('div', attrs={'id': 'signed-in'}) is not None

    def get_boggle(self):
        """Start a boggle game and return the boggle board.

        Raise a RuntimeError if boggle game cannot be started.

        :return Boggle object.
        """
        try:
            s = self._session.get(BOGGLE_URL)
        except requests.RequestException as e:
            raise RuntimeError(e) from e

        soup = BeautifulSoup(markup=s.text, features='lxml')
        boggle_table = soup.find('table', attrs={'id': 'pzl'})
        boggle_elements = [boggle_element.find('input')['value'] for
                           boggle_element in boggle_table.find_all('td')]
        return boggle_elements
