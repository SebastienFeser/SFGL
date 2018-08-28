from SFGE import *


class PlanetComponent(Component):
    body = None  # type: Body2d
    transform = None # type: Transform2d

    def init(self):
        self.body = self.get_component(Component.Body)
        self.transform = self.get_component(Component.Transform2d)
        self.screen_size = engine.config.screen_size

    def update(self, dt):
        pass