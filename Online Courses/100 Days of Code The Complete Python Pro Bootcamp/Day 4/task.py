import random

def rock_paper_scissors_print(choice):
    rock = '''
        _______
    ---'   ____)
          (_____)
          (_____)
          (____)
    ---.__(___)
    '''

    paper = '''
        _______
    ---'   ____)____
              ______)
              _______)
             _______)
    ---.__________)
    '''

    scissors = '''
        _______
    ---'   ____)____
              ______)
           __________)
          (____)
    ---.__(___)
    '''

    if choice == 0:
        print(rock)
    elif choice == 1:
        print(paper)
    elif choice == 2:
        print(scissors)
    else:
        print("You typed an invalid number, you lose!")

def rock_paper_scissors_condition(choice, computer_choice):
    if choice == computer_choice:
        print("It's a draw")
    elif choice == 0 and computer_choice == 1:
        print("You lose")
    elif choice == 1 and computer_choice == 2:
        print("You lose")
    elif choice == 2 and computer_choice == 0:
        print("You lose")
    else:
        print("You win!")

def rock_paper_scissors_game():

    choice = int(input("What do you choose? Type 0 for Rock, 1 for Paper or 2 for Scissors.\n"))
    rock_paper_scissors_print(choice)

    if choice in [0, 1, 2]:
        computer_choice = random.randint(0, 2)
        print(f"Computer chose {computer_choice}")
        rock_paper_scissors_print(computer_choice)
        rock_paper_scissors_condition(choice, computer_choice)


rock_paper_scissors_game()