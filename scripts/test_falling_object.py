from SFGE import *


class TestFallingObject(System):

    # init is like start in Unity
    def init(self):
        self.t = 0.0

    # update is like update
    def update(self, dt):
        self.t = 0.0
    # on_draw is used to draw the vectors
    def on_draw(self):
        self.t = 0.0

# rotating vector
