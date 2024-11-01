   std::cout << "Enter your username: ";
                std::cin >> enteredUsername;
                std::cout << "Enter your password: ";
                std::cin >> enteredPassword;
                for (User& user : users) {
                    if (user.authenticate(enteredUsername, enteredPassword)) {
                        std::cout << "Login successful!\n";
                        currentUser = user;  // Set the current user
                        foundUser = true;
                        performUserActions(buses, currentUser);  // Call the function for user options
                        break;
                    }
                }

                if (!foundUser) {
                    std::cout << "Invalid username or password. Try again.\n";
                }
                break;
            }
            case 2: {
                
                std::cout << "Enter a new username: ";
                std::cin >> enteredUsername;
                std::cout << "Enter a new password: ";
                std::cin >> enteredPassword;

                for (const User& user : users) {
                    if (user.getUsername() == enteredUsername) {
                        usernameTaken = true;
                        break;
                    }
                }

                if (usernameTaken) {
                    std::cout << "Username already taken. Try again.\n";
                } else {
                    
                    users.push_back(User(enteredUsername, enteredPassword));
                    currentUser = users.back();  
                    std::cout << "Registration successful!\n";
                    User::saveUsersToFile(users, "users.txt");
                    performUserActions(buses, currentUser); 
                }
                break;
            }
            case 3:
                // Back to Main Menu
                return;  // Exit the userMenu function
            default:
                std::cout << "Invalid 