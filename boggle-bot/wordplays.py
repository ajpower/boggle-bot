"""This module provides a Wordplays object to interact with wordplays.com."""
import requests

from bs4 import BeautifulSoup

LOGIN_URL = 'http://www.wordplays.com/wordgames/signin.pl'
BOGGLE_URL = 'http://www.wordplay.com/boggle'


class Wordplays:
    """A wordplays.com session.

    Provides methods for interacting with wordplays.com, including logging in
    and starting a boggle game.
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
        except requests.ConnectionError:
            raise RuntimeError('could not establish an internet connection.')
        except requests.Timeout:
            raise RuntimeError('connection attempt to wordplays.com timed out.')
        except requests.RequestException as e:
            raise RuntimeError(str(e))

        # If login was successful, the resulting HTML will contain a div with
        # id=signed-in.
        soup = BeautifulSoup(markup=s.text, features='lxml')
        return bool(soup.find('div', attrs={'id': 'signed-in'}))
