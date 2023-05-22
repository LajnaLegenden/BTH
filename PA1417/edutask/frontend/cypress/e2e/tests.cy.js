const chars = "abcdefghijklmnopqrstuvwxyz";
let email = "";

describe('Req 8', () => {
    //timeout
    Cypress.config('defaultCommandTimeout', 10000)

    //viewport
    Cypress.config('viewportWidth', 1280)
    Cypress.config('viewportHeight', 720)
    //before all
    before(() => {

        //genegate random email
        for (var i = 0; i < 10; i++) {
            email += chars[Math.floor(Math.random() * chars.length)];
        }
        email += "@gmail.com";


        cy.visit('http://localhost:3000')
        //click the second a tag
        cy.get('a').eq(1).click()
        cy.get('input[name="email"]').type(email)
        //type fistname
        cy.get('input[name="firstname"]').type("Max")
        //type lastname
        cy.get('input[name="lastname"]').type("Dahlgren")
        //ckick 
        cy.get('input[type="submit"]').click()
    });

    //before each
    beforeEach(() => {
        cy.visit('http://localhost:3000')
        cy.get('input[name="email"]').type(email)
        cy.get('input[type="submit"]').click()
        //delay
        cy.wait(1000)
    })

    //Describe
    describe('create a task', () => {
        let title = "";

        //before 
        before(() => {
            for (var i = 0; i < 10; i++) {
                title += chars[Math.floor(Math.random() * chars.length)];
            }
        })

        it('create a task with random title', () => {
            //type anytthing in title
            //GENERATE RANDOM STRING


            cy.get('input[name="title"]').type(title)
            //type anything in url
            cy.get('input[name="url"]').type("asdhjgasd")

            //click submit
            cy.get('input[type="submit"]').click()
            //delay
            cy.wait(1000)
            //find the task in the container > container-element > title-overlay element
            cy.get('.title-overlay').contains(title)
        })

        //add todo to task
        it('add todo to task', () => {
            //click the task with the title
            cy.get('.title-overlay').contains(title).click()
            //type anything in todo
            cy.get('.inline-form > [type="text"]').type("testTask")

            //delay
            cy.wait(1000)
            //click submit
            //click submit input within inline-form
            cy.get('.inline-form > [type="submit"]').click()
            //delay
            cy.wait(1000)
            //find all li in todo-list and check if it contains the text
            cy.get('.todo-list > li').contains("testTask")

        })

        //button is disabled when no todo text
        it('button is disabled when no todo text', () => {
            //click the task with the title
            cy.get('.title-overlay').contains(title).click()
            //type anything in todo

            cy.wait(1000)

            cy.get('.inline-form > [type="submit"]').should('be.disabled')
        });

        //test click todo item, should be marked as done and strikethrough
        it('test click todo item, should be marked as done and strikethrough', () => {
            //click the task with the title
            cy.get('.title-overlay').contains(title).click()
            //type anything in todo
            cy.wait(1000)

            //click .checker element within li with text testTask
            cy.get('.todo-list > li').contains("testTask").parent().find('.checker').click()
            //delay
            cy.wait(300)
            cy.get('.todo-list > li').contains("testTask").parent().find('.checker').click()
            //delay
            cy.wait(1000)
            //should have css  class checked    
            cy.get('.todo-list > li').contains("testTask").parent().find('.checker').should('have.class', 'checked')
        });

        //test click todo item, should be marked as done and strikethrough
        it('test click todo item, should NOT BE done anymore', () => {
            //click the task with the title
            cy.get('.title-overlay').contains(title).click()
            //type anything in todo
            cy.wait(1000)

            //click .checker element within li with text testTask
            cy.get('.todo-list > li').contains("testTask").parent().find('.checker').click()

            //delay
            cy.wait(1000)
            //should have css  class checked    
            cy.get('.todo-list > li').contains("testTask").parent().find('.checker').should('have.class', 'unchecked')
        });


        //test remove todo item
        describe('test remove todo item', () => {
            let taskName = "";

            //before
            before(() => {
                for (var i = 0; i < 10; i++) {
                    taskName += chars[Math.floor(Math.random() * chars.length)];
                }
            })

            beforeEach(() => {
                //add new todo
                cy.get('.title-overlay').contains(title).click()
                //type anything in todo
                cy.get('.inline-form > [type="text"]').type(taskName)
                //click submit
                //delay
                cy.wait(1000)
                cy.get('.inline-form > [type="submit"]').click()
                //delay
                cy.wait(1000)

            })

            it('test remove todo item', () => {
                //click .remove element within li with text testTask
                //delay
                cy.get('.todo-list > li').contains(taskName).parent().find('.remover').click()
                cy.get('.todo-list > li').contains(taskName).parent().find('.remover').click()
                cy.wait(1000)
                //should not contain taskname
                cy.get('.todo-list > li').should('not.contain', taskName)

            });
        });


    });

});
