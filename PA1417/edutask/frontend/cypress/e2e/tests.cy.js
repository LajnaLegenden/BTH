const chars = "abcdefghijklmnopqrstuvwxyz";
let email = "";

Cypress.config("defaultCommandTimeout", 10000);

//viewport
Cypress.config("viewportWidth", 1920);
Cypress.config("viewportHeight", 1080);
describe("Req 8", () => {
  let id;
  let taskId;
  let title;

  before(() => {
    //timeout

    //genegate random email
    for (var i = 0; i < 10; i++) {
      email += chars[Math.floor(Math.random() * chars.length)];
    }
    email += "@gmail.com";
    for (var i = 0; i < 10; i++) {
      title += chars[Math.floor(Math.random() * chars.length)];
    }
  });

  //before each
  beforeEach(() => {
    cy.request({
      method: "POST",
      url: "http://localhost:5000/users/create",
      form: true,
      body: {
        email: email,
        firstName: "Max",
        lastName: "Dahlgren",
      },
    }).then((response) => {
      id = response.body._id.$oid;

      console.log("ID AFTER", id);
      //Creae tasalj
      //
      // send a request to the server creating the new task
      cy.wrap(null).then(() => {
        const data = new URLSearchParams();
        data.append("title", title);
        data.append("description", "(add a description here)");
        data.append("userid", id);
        data.append("url", "google.se");
        data.append("todos", ["testTask"]);
        data.append("todos", ["anotherOne"]);

        fetch("http://localhost:5000/tasks/create", {
          method: "post",
          body: data,
        }).then((res) => {
          let json = res.json().then((json) => {
            console.log(json);
            taskId = json[0]._id.$oid;
          });
          expect(res.status).to.eq(200);
        });
      });
      cy.visit("http://localhost:3000");
      cy.get('input[name="email"]').type(email);
      cy.get('input[type="submit"]').click();
      //delay

      cy.wait(1000);

      cy.get(".title-overlay").contains(title).click();
    });
  });

  //Describe
  describe("R8UC1", () => {
    it("Main Succsess", () => {
      //click the task with the title
      //type anything in todo
      cy.get('.inline-form > [type="text"]').type("anotherTestTask");
      //delay
      cy.wait(1000);
      //click submit
      //click submit input within inline-form
      cy.get('.inline-form > [type="submit"]').click();
      //delay
      cy.wait(1000);
      //find all li in todo-list and check if it contains the text
      cy.get(".todo-list > li").contains("anotherTestTask");
    });

    it("Alternative", () => {
      cy.get('.inline-form > [type="submit"]').should("be.disabled");
    });

    //
    // //button is disabled when no todo text
    // it('TEST: Button is disabled when no todo text', () => {
    //     //click the task with the title
    //     cy.get('.title-overlay').contains(title).click()
    //     //type anything in todo
    //     //ensure that text field is empty
    //     cy.get('.inline-form > [type="text"]').clear()
    //     cy.wait(1000)
    //     cy.get('.inline-form > [type="submit"]').should('be.disabled')
    // });
    //
    // //test click todo item, should be marked as done and strikethrough
    // it('TEST: Test click todo item, should be marked as done and strikethrough', () => {
    //     //click the task with the title
    //     cy.get('.title-overlay').contains(title).click()
    //     //type anything in todo
    //     cy.wait(1000)
    //
    //     //click .checker element within li with text testTask
    //     cy.get('.todo-list > li').contains("testTask").parent().find('.checker').click()
    //     //delay
    //     cy.wait(300)
    //     cy.get('.todo-list > li').contains("testTask").parent().find('.checker').click()
    //     //delay
    //     cy.wait(1000)
    //     //should have css  class checked
    //     cy.get('.todo-list > li').contains("testTask").parent().find('.checker').should('have.class', 'checked')
    // });
    //
    // //test click todo item, should be marked as done and strikethrough
    // it('TEST: Test click todo item, should NOT BE done anymore', () => {
    //     //click the task with the title
    //     cy.get('.title-overlay').contains(title).click()
    //     //type anything in todo
    //     cy.wait(1000)
    //
    //     //click .checker element within li with text testTask
    //     cy.get('.todo-list > li').contains("testTask").parent().find('.checker').click()
    //
    //     //delay
    //     cy.wait(1000)
    //     //should have css  class checked
    //     cy.get('.todo-list > li').contains("testTask").parent().find('.checker').should('have.class', 'unchecked')
    // });
    //
    //
    // //test remove todo item
    // describe('TEST: Test remove todo item', () => {
    //     let taskName = "";
    //
    //     //before
    //     before(() => {
    //         for (var i = 0; i < 10; i++) {
    //             taskName += chars[Math.floor(Math.random() * chars.length)];
    //         }
    //     })
    //
    //     beforeEach(() => {
    //         //add new todo
    //         cy.get('.title-overlay').contains(title).click()
    //         //type anything in todo
    //         cy.get('.inline-form > [type="text"]').type(taskName)
    //         //click submit
    //         //delay
    //         cy.wait(1000)
    //         cy.get('.inline-form > [type="submit"]').click()
    //         //delay
    //         cy.wait(1000)
    //
    //     })
    //
    //     it('test remove todo item', () => {
    //         //click .remove element within li with text testTask
    //         //delay
    //         cy.get('.todo-list > li').contains(taskName).parent().find('.remover').click()
    //         cy.get('.todo-list > li').contains(taskName).parent().find('.remover').click()
    //         cy.wait(1000)
    //         //should not contain taskname
    //         cy.get('.todo-list > li').should('not.contain', taskName)
    //
    //     });
    // });
    //
    //
  });

  describe("R8UC2", () => {
    it("Main Succsess", () => {
      //click .checker element within li with text testTask
      cy.get(".todo-list > li")
        .contains("testTask")
        .parent()
        .find(".checker")
        .click();
      //delay
      cy.wait(1000);
      //should have css  class checked
      cy.get(".todo-list > li")
        .contains("testTask")
        .parent()
        .find(".checker")
        .should("have.class", "checked");
    });

    it("Alternative", () => {
      let todoId;

      cy.wrap(null).then(() => {
        cy.request({
          medthod: "GET",
          url: `http://localhost:5000/tasks/byid/${taskId}`,
        }).then((response) => {
          console.log("THE TASK", response.body);
          const todo = response.body.todos.filter(
            (todo) => todo.description === "anotherOne",
          );
          console.log(todo);
          todoId = todo[0]._id.$oid;
        });
      });

      cy.wrap(null).then(() => {
        fetch(`http://localhost:5000/todos/byid/${todoId}`, {
          method: "PUT",
          headers: {
            "User-Agent":
              "Mozilla/5.0 (X11; Linux x86_64; rv:127.0) Gecko/20100101 Firefox/127.0",
            Accept: "*/*",
            "Accept-Language": "en-US,en;q=0.5",
            "Accept-Encoding": "gzip, deflate, br, zstd",
            Referer: "http://localhost:3000/",
            "Cache-Control": "no-cache",
            "Content-Type": "application/x-www-form-urlencoded;charset=UTF-8",
            Origin: "http://localhost:3000",
            Connection: "keep-alive",
            "Sec-Fetch-Dest": "empty",
            "Sec-Fetch-Mode": "cors",
            "Sec-Fetch-Site": "same-site",
            Priority: "u=1",
          },
          body: new URLSearchParams({
            data: "{'$set': {'done': true}}",
          }),
        });
      });

      cy.get(".close-btn").click();

      //delay
      cy.wait(3000);
      //reopen the task
      cy.get(".title-overlay").contains(title).click();

      //click .close-btn
      cy.get(".close-btn").click();
      cy.wait(3000);

      //delay

      //reopen the task
      cy.get(".title-overlay").contains(title).click();

      cy.wait(5555);

      cy.get(".todo-list > li")
        .contains("anotherOne")
        .parent()
        .find(".checker")
        .click();

      cy.wait(1000);

      cy.get(".todo-list > li")
        .contains("anotherOne")
        .parent()
        .find(".checker")
        .should("not.have.class", "checked");

      cy.get(".todo-list > li")
        .contains("anotherOne")
        .parent()
        .find(".editable")
        //should have text-decoration line-through
        .should(
          "not.have.css",
          "text-decoration",
          "line-through solid rgb(49, 46, 46)",
        );
    });
  });

  describe("R8UC3", () => {
    it("Main Succsess", () => {
      cy.get(".todo-list > li")
        .contains("anotherOne")
        .parent()
        .find(".remover")
        .click();

      cy.wait(5000);

      cy.get(".todo-list > li").should("not.contain", "anotherOne");
    });
  });
  afterEach(() => {
    cy.request({
      method: "DELETE",
      url: `http://localhost:5000/users/${id}`,
    }).then((response) => {
      cy.log(response.body);
    });
  });
});
