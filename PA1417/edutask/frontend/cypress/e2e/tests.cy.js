const chars = "abcdefghijklmnopqrstuvwxyz";
let email = "";
import user from "../fixtures/cypress/fixtures/user.json";
import tasks from "../fixtures/cypress/fixtures/tasks.json";
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

    email = user.email;
    title = "Test Task";
  });

  //before each
  beforeEach(() => {
    cy.request({
      method: "POST",
      url: "http://localhost:5000/users/create",
      form: true,
      body: {
        email: email,
        firstName: user.firstName,
        lastName: user.lastName,
      },
    }).then((response) => {
      id = response.body._id.$oid;

      console.log("ID AFTER", id);
      //Creae tasalj
      //
      // send a request to the server creating the new task
      cy.wrap(null).then(() => {
        const data = new URLSearchParams();
        data.append("title", tasks.tasks[0].title);
        data.append("description", tasks.tasks[0].description);
        data.append("userid", id);
        data.append("url", tasks.tasks[0].url);
        for (let i = 0; i < tasks.tasks[0].todos.length; i++) {
          data.append("todos", tasks.tasks[0].todos[i]);
        }

        fetch("http://localhost:5000/tasks/create", {
          method: "post",
          body: data,
        })

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

      cy.get(".title-overlay").contains(tasks.tasks[0].title).click();
    });
  });

  //Describe
  describe("R8UC1", () => {
    it("Create todo", () => {
      //click the task with the title
      //type anything in todo
      cy.get('.inline-form > [type="text"]').type("Input 1");
      //delay
      cy.wait(1000);
      //click submit
      //click submit input within inline-form
      cy.get('.inline-form > [type="submit"]').click();
      //delay
      cy.wait(1000);
      //find all li in todo-list and check if it contains the text
      cy.get(".todo-list > li").contains("Input 1");
    });

    it("Dont create todo when input is empty", () => {
      cy.get('.inline-form > [type="text"]').should("have.value", "");
      cy.get('.inline-form > [type="submit"]').should("be.disabled");
    });
    describe("R8UC2", () => {
      it("Mark todo as done", () => {
        //click .checker element within li with text testTask
        cy.get(".todo-list > li")
          .contains(tasks.tasks[0].todos[0])
          .parent()
          .find(".checker")
          .click();
        //delay
        cy.wait(1000);
        //should have css  class checked
        cy.get(".todo-list > li")
          .contains(tasks.tasks[0].todos[0])
          .parent()
          .find(".checker")
          .should("have.class", "checked");
      });

      it("Mark done todo item as not done", () => {
        let todoId;

        cy.wrap(null).then(() => {
          cy.request({
            medthod: "GET",
            url: `http://localhost:5000/tasks/byid/${taskId}`,
          }).then((response) => {
            console.log("THE TASK", response.body);
            const todo = response.body.todos.filter(
              (todo) => todo.description === tasks.tasks[0].todos[1],
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
        cy.get(".title-overlay").contains(tasks.tasks[0].title).click();

        //click .close-btn
        cy.get(".close-btn").click();
        cy.wait(3000);

        //delay

        //reopen the task
        cy.get(".title-overlay").contains(tasks.tasks[0].title).click();

        cy.wait(5555);

        cy.get(".todo-list > li")
          .contains(tasks.tasks[0].todos[1])
          .parent()
          .find(".checker")
          .click();

        cy.wait(1000);

        cy.get(".todo-list > li")
          .contains(tasks.tasks[0].todos[1])
          .parent()
          .find(".checker")
          .should("not.have.class", "checked");

        cy.get(".todo-list > li")
          .contains(tasks.tasks[0].todos[1])
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
  });
  describe("R8UC3", () => {
    it("Remove todo", () => {
      cy.get(".todo-list > li")
        .contains(tasks.tasks[0].todos[1])
        .parent()
        .find(".remover")
        .click();

      cy.wait(5000);

      cy.get(".todo-list > li").should("not.contain", tasks.tasks[0].todos[1]);
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
