
class LoginAttempter:
    def attempt_login(self, user_name : str, password_hash : int) -> bool:
        if user_name == "adde":
            return True
        else:
            return False
