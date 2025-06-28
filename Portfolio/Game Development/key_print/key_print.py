import sys

import pygame

class KeyPrint:
    """Overall class to manage game assets and behavior."""

    def __init__(self):
        """Initialize the game, and create game resources."""
        pygame.init()

        self.clock = pygame.time.Clock()

        self.screen = pygame.display.set_mode((1200, 800))
        self.font = pygame.font.Font(pygame.font.get_default_font(), 80)
        self.text_surface = self.font.render("Hello World!", True, pygame.Color(0, 255, 0))
        pygame.display.set_caption("Key Print")

        # Set the background color.
        self.bg_color = (0, 0, 0)

    
    def run_game(self):
        """Start the main loop for the game."""
        while True:
            # Watch for keyboard and mouse events.
            self._check_events()
            self._update_screen()
            self.clock.tick(60)

    def _check_events(self):
        """Responds to keypresses and mouse events."""
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                key_string = str(event.key)
                self.text_surface = self.font.render(key_string, True, pygame.Color(0, 255, 0))
                

    def _update_screen(self):
        """Update images on the screen, and flip to the new screen."""
        self.screen.fill(self.bg_color)
        self.screen.blit(self.text_surface, dest = (350,350))

        pygame.display.flip()

if __name__ == '__main__':
    # Make a game instance, run the game.
    kp = KeyPrint()
    kp.run_game()